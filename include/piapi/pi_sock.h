#ifndef PI_SOCK_H
#define PI_SOCK_H
int pi_udpsock_recv(int fd, void *recvbuf, int *inout_bufsize);

int pi_udpsock_send(int fd,
                 char *receiver_ip,
                 int receiver_port,
                 void *data,
                 int len);

int pi_udpsock_bind(char *ipaddr,
                 int port,
                 char *dev);

#endif