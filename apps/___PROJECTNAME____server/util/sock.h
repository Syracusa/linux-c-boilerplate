#ifndef SOCK_H
#define SOCK_H
#include <stdio.h>
#include <errno.h>

int udpsock_recv(int fd,
                 void* recvbuf,
                 int* inout_bufsize);

int udpsock_send(int fd,
                 char* receiver_ip,
                 int receiver_port,
                 void* data,
                 int len);

int BindSocket(int type, int port);

int tcpsock_server(char* ipaddr,
                   int port,
                   char* dev);

int tcpsock_client(char* ipaddr,
                   int recvport,
                   int sendport,
                   char* dev);

int inet_sock_bind(char* ipaddr,
                   int port,
                   char* dev,
                   int sock_type);
#endif