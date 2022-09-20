#include "piapi.h"

#define MAX_MSGSIZE 65535

unsigned char msgbuf[MAX_MSGSIZE];

static size_t mmap_len = 0;
static void *mmap_addr = NULL;

#ifdef __WIN32
HANDLE hMapFile = INVALID_HANDLE_VALUE;
TCHAR szName[] = TEXT("LARGEPAGE");
LPCTSTR pBuf = NULL;
typedef int (*GETLARGEPAGEMINIMUM)(void);
#else
static int mmap_fd = -1;

#endif

#define MMAP_FNAME "tempfile.tmp"

void *get_mmap_ptr()
{
    return mmap_addr;
}

void free_mmapbuf()
{
#ifdef __WIN32
    UnmapViewOfFile(mmap_addr);
    CloseHandle(hMapFile);
#else
    if (mmap_fd != -1)
    {
        if (munmap(mmap_addr, mmap_len) == -1)
            perror("Error in munmap");

        if (close(mmap_fd))
            perror("Error in close");

        remove(MMAP_FNAME);

        mmap_fd = -1;
        mmap_addr = NULL;
    }
#endif
}

void write_mmapbuf(int pos, void *data, int len)
{
#ifdef __WIN32
    CopyMemory((PVOID)mmap_addr + pos, data, len);
#else
    unsigned char *buf = data;

    mmap_len += len;
    if (ftruncate(mmap_fd, mmap_len) != 0)
    {
        perror("Error extending file");
        return;
    }

    mmap_addr = mremap(mmap_addr, mmap_len - len, mmap_len, MREMAP_MAYMOVE);

    if (mmap_addr == MAP_FAILED)
    {
        perror("Error extending mapping");
        return;
    }
    memcpy(((uint8_t *)mmap_addr) + pos, buf, len);

    /* If write to disk is needed
        if((msync(addr,len,MS_SYNC)) < 0)
            perror("Error in msync");
    */
#endif
}

void init_mmapbuf()
{
#ifdef __WIN32
#define BUF_SIZE 1024 * 1024 * 1024 /* 1GB(temp)*/
    if (hMapFile == INVALID_HANDLE_VALUE)
    {
        hMapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE, // use paging file
            NULL,                 // default security
            PAGE_READWRITE,       // read/write access
            0,                    // maximum object size (high-order DWORD)
            BUF_SIZE,             // maximum object size (low-order DWORD)
            szName);              // name of mapping object

        if (hMapFile == NULL)
        {
            fprintf(stderr, "Could not create file mapping object (%d).\n", GetLastError());
            // _tprintf(TEXT("Could not create file mapping object (%d).\n"),
            //          GetLastError());
            return;
        }
        mmap_addr = MapViewOfFile(hMapFile,            // handle to map object
                                     FILE_MAP_ALL_ACCESS, // read/write permission
                                     0,
                                     0,
                                     BUF_SIZE);
    }
#else
    if (mmap_addr == NULL)
    {
        int ret;
        struct stat st;

        mmap_fd = open(MMAP_FNAME,
                       O_RDWR | O_CREAT,
                       S_IRWXU | S_IRGRP | S_IROTH);

        if (mmap_fd < 0)
        {
            fprintf(stderr, "Error in file opening");
            return;
        }

        if ((ret = fstat(mmap_fd, &st)) < 0)
        {
            fprintf(stderr, "Error in fstat");
            return;
        }

        mmap_len = st.st_size;
        if (mmap_len <= 0)
            mmap_len = 10;
        mmap_addr = mmap(NULL, mmap_len,
                         PROT_READ | PROT_WRITE, MAP_SHARED,
                         mmap_fd, 0);

        if (mmap_addr == MAP_FAILED)
        {
            fprintf(stderr, "Error in mmap.. %s\n", strerror(errno));
            fprintf(stderr, "Len %ld\n", mmap_len);
            abort();
        }
    }
    else
    {
        fprintf(stderr, "Already Initiated\n");
    }

#endif
}