#ifndef PLATFORM_H
#define PLATFORM_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#if defined(_WIN32)

    #undef _WIN32_WINNT
    #define _WIN32_WINNT 0x0600
    
    #include <winsock2.h>
    #include <winsock.h>
    #include <ws2tcpip.h>
    #include <synchapi.h>
    #include <windows.h>

    typedef uint32_t in_addr_t;
    typedef unsigned long sigset_t;

    #define bzero(b, len) (memset((b), '\0', (len)), (void)0)
    #define bcopy(b1, b2, len) (memmove((b2), (b1), (len)), (void)0)

    int clock_gettime(int f, struct timespec* ts);
#elif defined(__VXWORKS__)
    #include <ioLib.h>
    #include <tickLib.h>
    #include <sysLib.h>
    #include <vxWorks.h>
    #include <sockLib.h>
    #include <taskLib.h>
    #  define TTY_STRUCT int
    #  define sleep(a) taskDelay((a) * sysClkRateGet())

#elif defined(__linux__)
    #include <sys/select.h>
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    #include <sys/mman.h>
    #include <sys/types.h>
    #include <sys/stat.h>

    #include <netinet/ip.h>
    #include <netinet/in.h>

    #include <arpa/inet.h>
    #include <termios.h>
#else
    /* Unsupported platform */

#endif

void print_error();

#include "pi_sock.h"
#include "pi_mmap.h"
#include "pi_thread.h"
// #include "piapi.h"

#endif