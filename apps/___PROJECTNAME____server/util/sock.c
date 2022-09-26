
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>

int udpsock_recv(int fd,
                    void* recvbuf,
                    int* inout_bufsize)
{
    int res = 1;
    struct sockaddr_in rxaddr;
    socklen_t socklen = sizeof(struct sockaddr_in);

    int bufsize = *inout_bufsize;
    *inout_bufsize = recvfrom(fd, recvbuf, bufsize,
                              0, (struct sockaddr*)&rxaddr, &socklen);
    if (*inout_bufsize < 0)
    {
        res = -1;
        fprintf(stderr, "UDP Socket recv fail(FD %d\n", fd);
    }
    return res;
}


int udpsock_send(int fd,
                    char* receiver_ip,
                    int receiver_port,
                    void* data,
                    int len)
{
    struct sockaddr_in receiver_addr;

    receiver_addr.sin_family = AF_INET;

    uint16_t rport_u16 = receiver_port;

    inet_pton(AF_INET, receiver_ip, &receiver_addr.sin_addr);

    receiver_addr.sin_port = htons(rport_u16);
    int sendres = sendto(fd, data, len, 0,
                         (struct sockaddr*)&receiver_addr,
                         sizeof(receiver_addr));

    if (sendres < 0)
    {
        fprintf(stderr, "UDP Socket send fail(FD %d To %s %d)\n",
                fd, receiver_ip, receiver_port);
    }

    return sendres;
}

static void set_inetaddr(struct sockaddr_in* addr,
                         char* ip,
                         int port)
{
    int SOCK_LEN;
    SOCK_LEN = sizeof(addr);
    bzero((char*)addr, SOCK_LEN);
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr(ip);
    addr->sin_port = htons(port);
}

int pi_tcpsock_server(char* ipaddr,
                      int port,
                      char* dev)
{
    int tcpsock = inet_sock_bind(ipaddr, port, dev, SOCK_STREAM);

    int lres = listen(tcpsock, 1);
    if (lres == 0) {
        printf("TCP Listen Success\n");
    } else {
        printf("TCP Listen Fail %s\n", strerror(errno));
    }

    struct sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);

    int sock = accept(tcpsock, (struct sockaddr*)&addr, &addr_len);
    if (sock > 0) {
        printf("TCP Accept Success %d\n", sock);
    } else {
        printf("TCP Accept Fail %s\n", strerror(errno));
    }

    return sock;
}

void _be32_to_ipstr(in_addr_t addr, char* buf)
{
    uint8_t* ip_int = (uint8_t*)&addr;
    sprintf(buf, "%d.%d.%d.%d",
            ip_int[0], ip_int[1], ip_int[2], ip_int[3]);
}

#define _be32_to_ipstr_nobuf_bufsize 4
char* _be32_to_ipstr_nobuf(in_addr_t addr)
{
    static int bufidx = 0;
    static char ipstr[_be32_to_ipstr_nobuf_bufsize][40];
    if (bufidx > _be32_to_ipstr_nobuf_bufsize - 1)
        bufidx = 0;
    _be32_to_ipstr(addr, ipstr[bufidx]);

    return ipstr[bufidx++];
}

int pi_tcpsock_client(char* ipaddr,
                      int recvport,
                      int sendport,
                      char* dev)
{
    int sock;
    if (recvport != 0) {
        sock = inet_sock_bind(INADDR_ANY, recvport, dev, SOCK_STREAM);
        if (sock < 1) {
            fprintf(stderr, "TCP Socket bind fail %d %s\n",
                    sock, strerror(errno));
        }
    } else {
        fprintf(stderr, "No bind to port\n");
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == -1) {
            fprintf(stderr, "Socket create fail\n");
        }
    }

    uint16_t u16port = sendport;
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;

    inet_pton(AF_INET, ipaddr, &server_addr.sin_addr);
    server_addr.sin_port = htons(u16port);

    unsigned int addr_len = sizeof(server_addr);
    int cres;

    cres = connect(sock, (struct sockaddr*)&server_addr, addr_len);
    if (cres == 0) {
        printf("TCP Connect Success\n");
    } else {
        printf("TCP Connect Fail\n");
    }

    return sock;
}

int inet_sock_bind(char* ipaddr,
                      int port,
                      char* dev,
                      int sock_type)
{
    int reuse = 1;
    int sd, SOCK_LEN;
    struct sockaddr_in addr;

    if (ipaddr == NULL)
    {
        ipaddr = "0.0.0.0";
    }

    sd = socket(AF_INET, sock_type, 0);
    if (sd < 0)
    {
        printf("socket fail (ip=%s port=%d)\n", ipaddr, port);
    }

    set_inetaddr(&addr, ipaddr, port);

    SOCK_LEN = sizeof(addr);
    if (bind(sd, (struct sockaddr*)&addr, SOCK_LEN) < 0)
    {
        printf("Bind fail (ip=%s port=%d) : %s\n",
               ipaddr, port, strerror(errno));
    } else {
        printf("Bind success (ip=%s port=%d) %d\n",
               ipaddr, port, sd);
    }
    return sd;
}
