
#include <arpa/inet.h>
#include <sys/socket.h>
#include "log.h"

int udpsock_recv(int fd,
                 void *recvbuf,
                 int *inout_bufsize)
{
    struct sockaddr_in rxaddr;
    socklen_t socklen = sizeof(struct sockaddr_in);

    int bufsize = *inout_bufsize;
    *inout_bufsize = recvfrom(fd, recvbuf, bufsize,
                              0, (struct sockaddr *)&rxaddr, &socklen);
    if (*inout_bufsize < 0)
    {
        LOGF("UDP Socket recv fail(FD %d\n", fd);
        PRT_ERRNO();
    }
}

int udpsock_send(int fd,
                 char *receiver_ip,
                 int receiver_port,
                 void *data,
                 int len)
{
    struct sockaddr_in receiver_addr;

    receiver_addr.sin_family = AF_INET;

    uint16_t rport_u16 = receiver_port;
    receiver_addr.sin_port = htons(rport_u16);
    inet_aton(receiver_ip, &receiver_addr.sin_addr);

    int sendres = sendto(fd, data, len, 0,
                         (struct sockaddr *)&receiver_addr,
                         sizeof(receiver_addr));

    if (sendres < 0)
    {
        LOGF("UDP Socket send fail(FD %d To %s %d)\n",
             fd, receiver_ip, receiver_port);
        PRT_ERRNO();
    }

    return sendres;
}

static void set_inetaddr(struct sockaddr_in *addr,
                         char *ip,
                         int port)
{
    int SOCK_LEN;
    SOCK_LEN = sizeof(addr);
    bzero((char *)addr, SOCK_LEN);
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr(ip);
    addr->sin_port = htons(port);
}

int udpsock_bind(char *ipaddr,
                 int port,
                 char *dev)
{
    int reuse = 1;
    int sd, SOCK_LEN;
    struct sockaddr_in addr;

    if (ipaddr == NULL)
    {
        ipaddr = "0.0.0.0";
    }

    if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        LOGF("socket fail (ip=%s port=%d) : %s\n",
             ipaddr, port, strerror(errno));
        PRT_ERRNO();
    }

    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&reuse, sizeof(reuse)) < 0)
    {
        LOGF("Setting SO_REUSEADDR Error!!\n");
        PRT_ERRNO();
    }

    if (dev != NULL)
    {
        if (setsockopt(sd, SOL_SOCKET, SO_BINDTODEVICE,
                       dev, sizeof(dev)) < 0)
        {
            LOGF("SO_BINDTODEVICE (%s) ERROR!\n", strerror(errno));
            PRT_ERRNO();
        }
    }

    set_inetaddr(&addr, ipaddr, port);

    SOCK_LEN = sizeof(addr);
    if (bind(sd, (struct sockaddr *)&addr, SOCK_LEN) < 0)
    {
        LOGF("Bind fail (ip=%s port=%d) : %s\n",
             ipaddr, port, strerror(errno));
    }
    return sd;
}
