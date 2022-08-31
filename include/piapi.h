#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>
#include <time.h>

#if defined(_WIN32)
    #include <windows.h>
    #include <winsock.h>
    #include <winsock2.h>
    #include <memory>

    typedef uint32_t in_addr_t;
    typedef uint32_t socklen_t;
    typedef unsigned long sigset_t;

    #define bzero(b, len) (memset((b), '\0', (len)), (void)0)
    #define bcopy(b1, b2, len) (memmove((b2), (b1), (len)), (void)0)

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

    #include <netinet/ip.h>
    #include <netinet/in.h>

    #include <arpa/inet.h>
    #include <termios.h>
#else
    /* Unsupported platform */

#endif


// #include "platform.h"

#endif