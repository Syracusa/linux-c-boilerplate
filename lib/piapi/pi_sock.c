#include <stdio.h>
#include <errno.h>

#include "piapi.h"

int pi_udpsock_recv(int fd,
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
        fprintf(stderr, "UDP Socket recv fail(FD %d\n", fd);
    }
}

int pi_udpsock_send(int fd,
                    char *receiver_ip,
                    int receiver_port,
                    void *data,
                    int len)
{
    struct sockaddr_in receiver_addr;

    receiver_addr.sin_family = AF_INET;

    uint16_t rport_u16 = receiver_port;
    receiver_addr.sin_port = htons(rport_u16);
#ifndef __WIN32
    inet_pton(AF_INET, receiver_ip, &receiver_addr.sin_addr);
#else
    int socklen = sizeof(receiver_addr);
    WSAStringToAddressA(receiver_ip, AF_INET, NULL,
                        (struct sockaddr *)&receiver_addr,
                        &socklen);
#endif

    int sendres = sendto(fd, data, len, 0,
                         (struct sockaddr *)&receiver_addr,
                         sizeof(receiver_addr));

    if (sendres < 0)
    {
        fprintf(stderr, "UDP Socket send fail(FD %d To %s %d)\n",
                fd, receiver_ip, receiver_port);
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

int BindSocket(int type, int port)
{
	int sd, SOCK_LEN;
	struct sockaddr_in addr;

	if ((sd = socket(AF_INET, type, 0)) < 0)
	{
		printf("[BindSocket] socket fail (port=%d) : %s\n",
			   port,
			   strerror(errno));
	}

	SetInetAddr(&addr, port);

	SOCK_LEN = sizeof(addr);
	if (bind(sd, (struct sockaddr *)&addr, SOCK_LEN) < 0)
	{
		printf("[BindSocket] bind fail (port=%d) : %s\n",
			   port,
			   strerror(errno));
	}
#if 0
	struct timeval read_timeout;
	read_timeout.tv_sec = 0;
	read_timeout.tv_usec = 10;
	setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO,
			   &read_timeout, sizeof(read_timeout));
#endif
	return sd;
}

int pi_tcpsock_server(char *ipaddr,
                      int port,
                      char *dev)
{
    int tcpsock = pi_inet_sock_bind(ipaddr, port, dev, SOCK_STREAM);

    int lres = listen(tcpsock, 1);
    if (lres == 0){
        printf("TCP Listen Success\n");
    } else {
        printf("TCP Listen Fail %s\n", strerror(errno));
    }

    struct sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);

    int sock = accept(tcpsock, (struct sockaddr*) &addr, &addr_len);
    if (sock > 0){
        printf("TCP Accept Success %d\n", sock);
    } else {
        printf("TCP Accept Fail %s\n", strerror(errno));
    }

    return sock;
}

int pi_tcpsock_client(char *ipaddr,
                      int port,
                      char *dev)
{
    int sock = pi_inet_sock_bind(ipaddr, port, dev, SOCK_STREAM);
    uint16_t u16port = port;
    struct sockaddr_in server_addr;
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(u16port);

#ifndef __WIN32
    inet_pton(AF_INET, ipaddr, &server_addr.sin_addr);
#else
    int socklen = sizeof(server_addr);
    WSAStringToAddressA(ipaddr, AF_INET, NULL,
                        (struct sockaddr *)&server_addr,
                        &socklen);
#endif
    unsigned int addr_len = sizeof(server_addr);
    int cres;

    cres = connect(sock, (struct sockaddr*)&server_addr, addr_len);
    if (cres == 0){
        printf("TCP Connect Success\n");
    } else {
        printf("TCP Connect Fail %s\n", strerror(errno));
    }

    return sock;
}

int pi_inet_sock_bind(char *ipaddr,
                    int port,
                    char *dev,
                    int sock_type)
{
#ifdef __WIN32
    static int init = 0;
    if (init == 0)
    {
        WSADATA wsadata;
        WSAStartup(MAKEWORD(2, 2), &wsadata);
        init = 1;
    }
#endif
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
        printf("socket fail (ip=%s port=%d) : %s\n",
               ipaddr, port, strerror(errno));
#ifdef __WIN32
        printf("Error code : %d\n", WSAGetLastError());
#endif
    }

#ifndef __WIN32
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,
                   (char *)&reuse, sizeof(reuse)) < 0)
    {
        printf("Setting SO_REUSEADDR Error!!\n");
    }

    if (dev != NULL)
    {
        if (setsockopt(sd, SOL_SOCKET, SO_BINDTODEVICE,
                       dev, sizeof(dev)) < 0)
        {
            printf("SO_BINDTODEVICE (%s) ERROR!\n", strerror(errno));
        }
    }
#endif
    set_inetaddr(&addr, ipaddr, port);

    SOCK_LEN = sizeof(addr);
    if (bind(sd, (struct sockaddr *)&addr, SOCK_LEN) < 0)
    {
        printf("Bind fail (ip=%s port=%d) : %s\n",
               ipaddr, port, strerror(errno));
    }
    return sd;
}
