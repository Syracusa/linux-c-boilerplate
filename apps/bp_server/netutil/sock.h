#ifndef SOCK_H
#define SOCK_H (1)

int udpsock_recv(int fd, void *recvbuf, int *inout_bufsize);

int udpsock_send(int fd,
                 char *receiver_ip,
                 int receiver_port,
                 void *data,
                 int len);

int udpsock_bind(char *ipaddr, int port, char *dev);

#endif