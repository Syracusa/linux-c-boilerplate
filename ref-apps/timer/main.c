#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define TIMER_NUM 30
static timer_t timerid[TIMER_NUM + 1];

static void handler(int sig, siginfo_t *si, void *uc)
{
    for (int i = 0; i < 1; i++)
    {
        struct timespec currtime;
        clock_gettime(CLOCK_REALTIME, &currtime);
        printf("[%ld:%ld]sig %d log %d TEST LOG1\n",
               currtime.tv_sec % 1000,
               currtime.tv_nsec / 1000000,
               sig, i);
        fflush(stdout);
        printf("[%ld:%ld]sig %d log %d TEST LOG2\n",
               currtime.tv_sec % 1000,
               currtime.tv_nsec / 1000000,
               sig, i);
        fflush(stdout);
        printf("[%ld:%ld]sig %d log %d TEST LOG3\n",
               currtime.tv_sec % 1000,
               currtime.tv_nsec / 1000000,
               sig, i);
        fflush(stdout);
    }
}

void register_rttimers(int sec)
{
    for (int i = 0; i < TIMER_NUM; i++)
    {
        int timeridx = i + TIMER_NUM;

        struct itimerspec its;
        sigset_t mask;
        int signum = SIGRTMIN + i;

        /* Start the timer */
        its.it_value.tv_sec = sec;
        its.it_value.tv_nsec = 0;
        its.it_interval.tv_sec = 0;
        its.it_interval.tv_nsec = 0;

        if (timer_settime(timerid[i], 0, &its, NULL) == -1)
        {
            fprintf(stderr, "TIMER SETTIME ERROR!!!\n");
            return;
        }

        /* Unlock the timer signal, so that timer notification
            can be delivered */
        sigemptyset(&mask);
        sigaddset(&mask, signum);
        if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
        {
            fprintf(stderr, "TIMER sigprocmask ERROR!!!\n");
            return;
        }

        fprintf(stderr, "Timer %d registerd\n", timeridx);
    }
}

static void create_rttimers()
{
    struct sigevent sev;
    struct sigaction sa;
    sigset_t mask;
    int signum, i;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;

    for (i = 0; i < TIMER_NUM; i++)
    {
        signum = SIGRTMIN + i;

        /* Establish handler for timer signal */
        sigemptyset(&sa.sa_mask);
        if (sigaction(signum, &sa, NULL) == -1)
            exit(2);

        /* Block timer signal temporarily */
        printf("Blocking signal %d\n", signum);
        sigemptyset(&mask);
        sigaddset(&mask, signum);
        if (sigprocmask(SIG_SETMASK, &mask, NULL) == -1)
            exit(2);

        /* Create the timer */
        sev.sigev_notify = SIGEV_SIGNAL;
        sev.sigev_signo = signum;
        sev.sigev_value.sival_ptr = &timerid[i];
        if (timer_create(CLOCK_REALTIME, &sev, &timerid[i]) == -1)
            exit(2);
    }
}

int main()
{
    create_rttimers();
    register_rttimers(1);
    sleep(2);
    return 0;
}