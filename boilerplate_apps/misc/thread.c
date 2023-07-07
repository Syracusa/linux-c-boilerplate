#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t thr;
int stop_thread = 0;

static void *threaded_work(void *arg)
{
    /* Masking SIGINT so main thread can receive SIGINT */
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    pthread_sigmask(SIG_BLOCK, &sigset, NULL);

    int *argint = (int *)arg;
    while (!stop_thread) {
        printf("Hello from thread... Arg: %d\n", *argint);
        sleep(3);
    }
}

void handle_sigint(int sig)
{
    fprintf(stderr, "SIGINT\n");
    stop_thread = 1;
    printf("Wait join...\n");
    pthread_join(thr, NULL);
    printf("Joined\n");
    exit(0);
}

int main()
{
    int arg = 42;
    signal(SIGINT, handle_sigint);
    pthread_create(&thr, NULL, (void *)threaded_work, &arg);
    sleep(100);
}