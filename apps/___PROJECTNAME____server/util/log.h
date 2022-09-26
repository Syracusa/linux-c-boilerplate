#ifndef LOG_H_
#define LOG_H_ (1)

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#ifndef LOG_LEVEL
#define LOG_LEVEL (7)
#endif

#ifndef LOG_COLOR
#define LOG_COLOR (1)
#endif

// log levels the same as syslog
#define FATAL (1)
#define CRIT (2)
#define ERR (3)
#define WARNING (4)
#define NOTICE (5)
#define INFO (6)
#define DEBUG (7)

// colors
#define NONE "\e[0m"
#define BLACK "\e[0;40m"
#define L_BLACK "\e[1;30m"
#define RED "\e[0;41m"
#define L_RED "\e[1;31m"
#define GREEN "\e[0;42m"
#define L_GREEN "\e[1;32m"
#define BROWN "\e[0;43m"
#define YELLOW "\e[1;43m"
#define BLUE "\e[0;44m"
#define L_BLUE "\e[1;34m"
#define PURPLE "\e[0;45m"
#define L_PURPLE "\e[1;35m"
#define CYAN "\e[0;46m"
#define L_CYAN "\e[1;36m"
#define GRAY "\e[0;47m"
#define WHITE "\e[1;37m"

#define BOLD "\e[1m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define REVERSE "\e[7m"
#define HIDE "\e[8m"
#define CLEAR "\e[2J"
#define CLRLINE "\r\e[K" // or "\e[1K\r"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

/* safe readable version of errno */
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define LIBLOGHDR "[SRV] "

/* Log macro */
#define LOGF(M, ...)                                              \
    do                                                            \
    {                                                             \
        fprintf(stderr, RED "F" NONE LIBLOGHDR M, ##__VA_ARGS__); \
    } while (0)
#define LOGC(M, ...)                                                 \
    do                                                               \
    {                                                                \
        fprintf(stderr, YELLOW "C" NONE LIBLOGHDR M, ##__VA_ARGS__); \
    } while (0)
#define LOGE(M, ...)                                                \
    do                                                              \
    {                                                               \
        fprintf(stderr, BROWN "E" NONE LIBLOGHDR M, ##__VA_ARGS__); \
    } while (0)
#define LOGW(M, ...)                                               \
    do                                                             \
    {                                                              \
        fprintf(stderr, BLUE "W" NONE LIBLOGHDR M, ##__VA_ARGS__); \
    } while (0)
#define LOGN(M, ...)                                               \
    do                                                             \
    {                                                              \
        fprintf(stderr, CYAN "N" NONE LIBLOGHDR M, ##__VA_ARGS__); \
    } while (0)
#define LOGI(M, ...)                                                \
    do                                                              \
    {                                                               \
        fprintf(stderr, GREEN "I" NONE LIBLOGHDR M, ##__VA_ARGS__); \
    } while (0)
#define LOGD(M, ...)                                               \
    do                                                             \
    {                                                              \
        fprintf(stderr, GRAY "D" NONE LIBLOGHDR M, ##__VA_ARGS__); \
    } while (0)

/* Log macro with where */
#define WLOGF(M, ...)                                                                                             \
    do                                                                                                            \
    {                                                                                                             \
        fprintf(stderr, RED "F" NONE LIBLOGHDR "%s (%s:%d) " M, __func__, __FILENAME__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#define WLOGC(M, ...)                                                                                                \
    do                                                                                                               \
    {                                                                                                                \
        fprintf(stderr, YELLOW "C" NONE LIBLOGHDR "%s (%s:%d) " M, __func__, __FILENAME__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#define WLOGE(M, ...)                                                                                               \
    do                                                                                                              \
    {                                                                                                               \
        fprintf(stderr, BROWN "E" NONE LIBLOGHDR "%s (%s:%d) " M, __func__, __FILENAME__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#define WLOGW(M, ...)                                                                                              \
    do                                                                                                             \
    {                                                                                                              \
        fprintf(stderr, BLUE "W" NONE LIBLOGHDR "%s (%s:%d) " M, __func__, __FILENAME__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#define WLOGN(M, ...)                                                                                              \
    do                                                                                                             \
    {                                                                                                              \
        fprintf(stderr, CYAN "N" NONE LIBLOGHDR "%s (%s:%d) " M, __func__, __FILENAME__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#define WLOGI(M, ...)                                                                                               \
    do                                                                                                              \
    {                                                                                                               \
        fprintf(stderr, GREEN "I" NONE LIBLOGHDR "%s (%s:%d) " M, __func__, __FILENAME__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#define WLOGD(M, ...)                                                                                              \
    do                                                                                                             \
    {                                                                                                              \
        fprintf(stderr, GRAY "D" NONE LIBLOGHDR "%s (%s:%d) " M, __func__, __FILENAME__, __LINE__, ##__VA_ARGS__); \
    } while (0)

/* Log macro with Time */
#define _GET_CURRTIME(_tbuf)                                                   \
    do                                                                         \
    {                                                                          \
        struct timespec _ts;                                                   \
        clock_gettime(CLOCK_REALTIME, &_ts);                                   \
        sprintf(_tbuf, "[%4lu:%4lu] ", _ts.tv_sec % 1000, _ts.tv_nsec / 1000); \
    } while (0);

#define TLOGF(M, ...)                                                          \
    do                                                                         \
    {                                                                          \
        char _tbuf[20];                                                        \
        _GET_CURRTIME(_tbuf);                                                  \
        fprintf(stderr, RED "F" NONE LIBLOGHDR "%s " M, _tbuf, ##__VA_ARGS__); \
    } while (0)
#define TLOGC(M, ...)                                                             \
    do                                                                            \
    {                                                                             \
        char _tbuf[20];                                                           \
        _GET_CURRTIME(_tbuf);                                                     \
        fprintf(stderr, YELLOW "C" NONE LIBLOGHDR "%s " M, _tbuf, ##__VA_ARGS__); \
    } while (0)
#define TLOGE(M, ...)                                                            \
    do                                                                           \
    {                                                                            \
        char _tbuf[20];                                                          \
        _GET_CURRTIME(_tbuf);                                                    \
        fprintf(stderr, BROWN "E" NONE LIBLOGHDR "%s " M, _tbuf, ##__VA_ARGS__); \
    } while (0)
#define TLOGW(M, ...)                                                           \
    do                                                                          \
    {                                                                           \
        char _tbuf[20];                                                         \
        _GET_CURRTIME(_tbuf);                                                   \
        fprintf(stderr, BLUE "W" NONE LIBLOGHDR "%s " M, _tbuf, ##__VA_ARGS__); \
    } while (0)
#define TLOGN(M, ...)                                                           \
    do                                                                          \
    {                                                                           \
        char _tbuf[20];                                                         \
        _GET_CURRTIME(_tbuf);                                                   \
        fprintf(stderr, CYAN "N" NONE LIBLOGHDR "%s " M, _tbuf, ##__VA_ARGS__); \
    } while (0)
#define TLOGI(M, ...)                                                            \
    do                                                                           \
    {                                                                            \
        char _tbuf[20];                                                          \
        _GET_CURRTIME(_tbuf);                                                    \
        fprintf(stderr, GREEN "I" NONE LIBLOGHDR "%s " M, _tbuf, ##__VA_ARGS__); \
    } while (0)
#define TLOGD(M, ...)                                                           \
    do                                                                          \
    {                                                                           \
        char _tbuf[20];                                                         \
        _GET_CURRTIME(_tbuf);                                                   \
        fprintf(stderr, GRAY "D" NONE LIBLOGHDR "%s " M, _tbuf, ##__VA_ARGS__); \
    } while (0)

#define PRT_ERRNO()                                     \
    do                                                  \
    {                                                   \
        fprintf(stderr, "errno : %s\n", clean_errno()); \
    } while (0)

/* LOG_LEVEL controls */
#if LOG_LEVEL < DEBUG
#undef LOGD
#undef WLOGD
#undef TLOGD
#define LOGD(M, ...) \
    do               \
    {                \
    } while (0)
#define WLOGD(M, ...) \
    do                \
    {                 \
    } while (0)
#define TLOGD(M, ...) \
    do                \
    {                 \
    } while (0)
#endif

#if LOG_LEVEL < INFO
#undef LOGI
#undef WLOGI
#undef TLOGI
#define LOGI(M, ...) \
    do               \
    {                \
    } while (0)
#define WLOGI(M, ...) \
    do                \
    {                 \
    } while (0)
#define TLOGI(M, ...) \
    do                \
    {                 \
    } while (0)
#endif

#if LOG_LEVEL < NOTICE
#undef LOGN
#undef WLOGN
#undef TLOGN
#define LOGN(M, ...) \
    do               \
    {                \
    } while (0)
#define WLOGN(M, ...) \
    do                \
    {                 \
    } while (0)
#define TLOGN(M, ...) \
    do                \
    {                 \
    } while (0)
#endif

#if LOG_LEVEL < WARNING
#undef LOGW
#undef WLOGW
#undef TLOGW
#define LOGW(M, ...) \
    do               \
    {                \
    } while (0)
#define WLOGW(M, ...) \
    do                \
    {                 \
    } while (0)
#define TLOGW(M, ...) \
    do                \
    {                 \
    } while (0)
#endif

#if LOG_LEVEL < ERR
#undef LOGE
#undef WLOGE
#undef TLOGE
#define LOGE(M, ...) \
    do               \
    {                \
    } while (0)
#define WLOGE(M, ...) \
    do                \
    {                 \
    } while (0)
#define TLOGE(M, ...) \
    do                \
    {                 \
    } while (0)
#endif

#if LOG_LEVEL < CRIT
#undef LOGC
#undef WLOGC
#undef TLOGC
#define LOGC(M, ...) \
    do               \
    {                \
    } while (0)
#define WLOGC(M, ...) \
    do                \
    {                 \
    } while (0)
#define TLOGC(M, ...) \
    do                \
    {                 \
    } while (0)
#endif

#if LOG_LEVEL < FATAL
#undef LOGF
#undef WLOGF
#undef TLOGF
#define LOGF(M, ...) \
    do               \
    {                \
    } while (0)
#define WLOGF(M, ...) \
    do                \
    {                 \
    } while (0)
#define TLOGF(M, ...) \
    do                \
    {                 \
    } while (0)
#endif

/* LOG_COLOR controls */
#if LOG_COLOR < 1

#undef NONE
#define NONE

#undef RED
#define RED

#undef PURPLE
#define PURPLE

#undef YELLOW
#define YELLOW

#undef BROWN
#define BROWN

#undef GREEN
#define GREEN

#undef CYAN
#define CYAN

#undef BLUE
#define BLUE

#undef GRAY
#define GRAY

#endif


#if IS_RELEASE_BUILD
    #define ASSERT(expr) do { if (!(expr)){ \
        printf("[%s:%d]Assertion failed\n", __FILENAME__, __LINE__); \
        LOG_COMMON(LL_FATAL, LF_WHERE, "Assertion failed\n"); \
        } \
    }while (0)
#else 
    #define ASSERT(expr) do { if (!(expr)){ \
        WLOGF("Assertion failed\n"); \
        abort();} \
    }while (0)
#endif



#endif