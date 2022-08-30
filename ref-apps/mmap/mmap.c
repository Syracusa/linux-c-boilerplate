#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <errno.h>

#define MAX_MSGSIZE 65535

unsigned char msgbuf[MAX_MSGSIZE];

static int mmap_fd = -1;
static void *mmap_addr = NULL;
static size_t mmap_len = 0;
#define MMAP_FNAME "tempfile.tmp"

void free_mmapbuf()
{
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
}

void write_mmapbuf(int pos, void *data, int len)
{
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
}

void init_mmapbuf()
{
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
}

#define WBUFSZ  4000
#define WNUM    100000
int main(){
    init_mmapbuf();
    
    char buf[WBUFSZ];
    memset(buf, 0xfa, WBUFSZ);
    
    for (int i = 0; i < WNUM; i++){
        fprintf(stderr, "Try write Seq:%d\n", i);
        write_mmapbuf(i * WBUFSZ, buf, WBUFSZ);
    }

    int failcnt = 0;
    for (int i = 0; i < WNUM; i++){
        fprintf(stderr, "Try check Seq:%d\n", i);
        int cmpres = memcmp(((uint8_t*)mmap_addr) + i * WBUFSZ, buf, WBUFSZ);
        if (cmpres != 0){
            failcnt++;
            fprintf(stderr, "FAIL(%d)\n", cmpres);
        }
    }

    fprintf(stderr, "FAIL COUNT : %d\n", failcnt);

    free_mmapbuf();
    return 0;
}