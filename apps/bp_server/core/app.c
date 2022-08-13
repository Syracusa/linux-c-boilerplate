#include <stdio.h>

#include "app.h"
#include "sock.h"

AppContext app;

static void init_io(IoContext *ioc)
{
    ioc->blocktime.tv_sec = 1;
    ioc->blocktime.tv_usec = 0;

    ioc->udp_sock = udpsock_bind(app.cfg.ipstr, app.cfg.port, NULL);
    if (ioc->udp_sock < 0)
    {
        LOGF("UDP Socket bind fail\n");
        ASSERT(0);
    }
    if (ioc->fdmax <= ioc->udp_sock)
    {
        ioc->fdmax = ioc->udp_sock + 1;
    }

    FD_SET(ioc->udp_sock, &ioc->fds_env);
}

void init_app(char* config_filename)
{
    memset(&app, 0x00, sizeof(AppContext));

    parse_config(&app.cfg, config_filename);
    init_io(&app.ioc);
}