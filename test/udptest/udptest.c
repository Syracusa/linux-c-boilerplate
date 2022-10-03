#include "piapi.h"

#define TEST_DATA "Hello world!"

static pi_thread_ret_t do_client(void *arg){
    int sock = pi_tcpsock_client("0.0.0.0", 0, 39992, NULL);

    while (1){
        write(sock, TEST_DATA, strlen(TEST_DATA) + 1);
        printf("Send to Server...\n");
    }
    return PI_THREAD_DONE;
}

static int do_server(){
    int sock = pi_tcpsock_server("0.0.0.0", 39992, NULL);

    char recvbuf[100];
    
    int bufsize = 100;
    read(sock, recvbuf, bufsize);
    printf("Recv from client : %s\n", recvbuf);

    int cmpres = strcmp(recvbuf, TEST_DATA);
    if (cmpres == 0){
        return 0;
    } else {
        return -1;
    }
}

int main(){
    pi_thread_t t;
    pi_thread_create(&t, do_client, NULL);
    
    return do_server();
}