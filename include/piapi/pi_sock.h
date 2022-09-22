#ifndef PI_SOCK_H
#define PI_SOCK_H
#include <stdio.h>
#include <errno.h>

#include "piapi.h"

int pi_udpsock_recv(int fd,
                    void *recvbuf,
                    int *inout_bufsize);

int pi_udpsock_send(int fd,
                    char *receiver_ip,
                    int receiver_port,
                    void *data,
                    int len);

int BindSocket(int type, int port);

int pi_tcpsock_server(char *ipaddr,
                      int port,
                      char *dev);
                      
int pi_tcpsock_client(char *ipaddr,
                      int recvport,
                      int sendport,
                      char *dev);

int pi_inet_sock_bind(char *ipaddr,
                      int port,
                      char *dev,
                      int sock_type);
#endif