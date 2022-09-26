#ifndef APP_H
#define APP_H

#include "log.h"
#include "cfg.h"

typedef struct IoContext{
    /* Read File Descriptor Bitmap */
    fd_set	fds_env; 	 

    /* descriptor max num */
    int		fdmax;

    struct timeval blocktime;

    int udp_sock;
} IoContext;

typedef struct AppContext{
    AppConfig cfg;
    IoContext ioc;
} AppContext;

extern AppContext app;

void init_app(char* config_filename);

#endif