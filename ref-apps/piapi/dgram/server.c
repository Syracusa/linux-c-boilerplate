#include "piapi.h"

int main(){
    int sock = pi_inet_sock_bind("0.0.0.0", 39992, NULL, SOCK_DGRAM);

    char recvbuf[100];
    while (1){
        int bufsize = 100;
        pi_udpsock_recv(sock, recvbuf, &bufsize);
        printf("Recv from client : %s\n", recvbuf);
    }
}
