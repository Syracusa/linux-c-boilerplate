#include "sock.h"
#include "server.h"
#include "log.h"
#include "util.h"

#include <unistd.h>

#define UDP_BUFSIZE 5000

static int server_loop = 1;

static void init_server()
{
    LOGI("Initialize server...\n");
}

static void server_udp_recv()
{
    static char recvbuf[UDP_BUFSIZE];
    int recvlen = UDP_BUFSIZE;
    udpsock_recv(app.ioc.udp_sock, recvbuf, &recvlen);

    hexdump(recvbuf, recvlen, stderr);
}

static void server_select()
{
    fd_set fds = app.ioc.fds_env;
    struct timeval tv = app.ioc.blocktime;
    int rts = 0;

    LOGD("Select waiting...\n");
    rts = select(app.ioc.fdmax, &fds, (fd_set *)0, (fd_set *)0, &tv);

    if (rts > 0)
    {
        if (app.ioc.udp_sock)
        {
            server_udp_recv();
        }
    }
}

static void server_finalize()
{
    LOGI("Finalize server...\n");
}

void server_stop()
{
    server_loop = 0;
}

static void send_dummy()
{
    char dummydata[100] = "Hello world!\n";

    udpsock_send(app.ioc.udp_sock,
                 app.cfg.target_ipstr,
                 app.cfg.target_port,
                 dummydata,
                 100);
}

void server_start()
{
    init_server();

    server_loop = 1;
    while (server_loop)
    {
        send_dummy();
        server_select();

        usleep(500000);
    }

    server_finalize();
}
