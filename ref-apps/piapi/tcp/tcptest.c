#include <stdio.h>

#include "piapi.h"

static void usage(char* pname){
    fprintf(stderr, "Usage : %s s|c\n", pname);
    exit(2);
}

int main(int argc, char* argv[])
{
    if (argc != 2){
        usage(argv[0]);
    }

    int sock;
    char buf[100];

    char* me;
    char* peer;

    if (argv[1][0] == 's'){
        printf("Server mode\n");
        sock = pi_tcpsock_server(INADDR_ANY, 5551, NULL);
        me = "Server";
        peer = "Client";
    } else {
        printf("Client mode\n");
        sock = pi_tcpsock_client("127.0.0.1", 0, 5551, NULL);
        me = "Client";
        peer = "Server";
    }

    snprintf(buf, 100, "Hello %s, I'm %s\n", peer, me);

    if (sock < 1){
        printf("Get tcpsock fail %d\n", sock);
    }
 #ifdef __WIN32
    int wlen = send(sock, buf, 100, 0);
    int rlen = recv(sock, buf, 100, 0);
#else
    int wlen = write(sock, buf, 100);
    int rlen = read(sock, buf, 100);
#endif
    if (wlen <= 0 || rlen <= 0){
#ifdef __WIN32
        printf("Error code %d %d  %d\n",wlen, rlen, WSAGetLastError());
#else
        printf("Error. %d, %d %s\n",wlen, rlen, strerror(errno));
#endif
    } else {
        printf("Write %d bytes and Read %d bytes\n", wlen, rlen);
        printf("Recvfrom %s... %s", peer, buf);
    }

}