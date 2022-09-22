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
 
    write(sock, buf, 100);
    read(sock, buf, 100);

    printf("Recvfrom %s... %s", peer, buf);
}