#include <stdio.h>
#include <signal.h>
#include <sys/socket.h>
#include <stdlib.h>

#include "sock.h"
#include "app.h"

AppContext app;

static void init_io(IoContext *ioc)
{
    ioc->blocktime.tv_sec = 1;
    ioc->blocktime.tv_usec = 0;

    ioc->udp_sock = inet_sock_bind(app.cfg.ipstr,
                                      app.cfg.port,
                                      NULL,
                                      SOCK_DGRAM);
    if (ioc->udp_sock < 0)
    {
        LOGF("UDP Socket bind fail\n");
        exit(2);
    }
    if (ioc->fdmax <= ioc->udp_sock)
    {
        ioc->fdmax = ioc->udp_sock + 1;
    }

    FD_SET(ioc->udp_sock, &ioc->fds_env);
}

void quit()
{
    LOGF("App recived interrupt signal\n");
    exit(2);
}

void init_app(char *config_filename)
{
    signal(SIGINT, quit);
    memset(&app, 0x00, sizeof(AppContext));

    parse_config(&app.cfg, config_filename);
    init_io(&app.ioc);
}