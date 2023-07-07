#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h> 

void check_child_alive(pid_t pid)
{
    int res = kill(pid, 0);
    if (res == 0) {
        printf("Child is alive\n");
    } else {
        printf("Child is dead %d\n", res);
    }
}

void sigint_child(int sig)
{
    printf("Child process - SIGINT\n");
    exit(0);
}

void sigchld_parent(int sig)
{
    printf("Parent process - SIGCHLD\n");
    pid_t p;
    int status;

    while ((p = waitpid(-1, &status, WNOHANG)) != -1) {
        /* Handle the death of pid p */
        printf("Child %d is dead\n", p);
        exit(0);
    }
}

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
        /* Child process */
        signal(SIGINT, sigint_child);
        int i = 0;
        while (1) {
            printf("Child process - %d\n", i++);
            sleep(1);
        }
    } else {
        /* Parent process */
        printf("Parent process - Child PID:%d\n", pid);
        signal(SIGCHLD, sigchld_parent);

        while (1) {
            check_child_alive(pid);
            sleep(1);
            kill(pid, SIGINT);
        }
    }

    return 0;
}