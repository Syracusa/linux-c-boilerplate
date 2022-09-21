#include "piapi.h"

int main(){
    int sock = pi_inet_sock_bind("0.0.0.0", 39991, NULL, SOCK_DGRAM);

    while (1){
        pi_udpsock_send(sock, "127.0.0.1", 39992, "Hello world!", 13);
        printf("Send to Server...\n");
        sleep(1);
    }
}