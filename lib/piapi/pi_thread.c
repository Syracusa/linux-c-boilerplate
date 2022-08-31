#include "piapi.h"

pi_mutex_t *pi_mutex_new()
{
    pi_mutex_t* mt;
#ifdef __WIN32
    mt = malloc(sizeof(SRWLOCK));
    InitializeSRWLock((SRWLOCK *)mt);
#else
    mt = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init((pthread_mutex_t *)mt, NULL);
#endif
}

void pi_mutex_free(pi_mutex_t *mt)
{
    if (mt != NULL)
    {
        free(mt);
    }
}

void pi_mutex_lock(pi_mutex_t *mt)
{
#ifdef __WIN32
    AcquireSRWLockShared(mt);
#else
    pthread_mutex_lock(mt);
#endif
}

void pi_mutex_unlock(pi_mutex_t *mt)
{
#ifdef __WIN32
    AcquireSRWLockExclusive(mt);
#else
    pthread_mutex_unlock(mt);
#endif
}

void pi_thread_create(pi_thread_t *t, pi_thread_ret_t routine(void *), void *arg)
{
#ifdef __WIN32
    *t = CreateThread(NULL, 0, routine, *(void **)&arg, 0, NULL);
#else
    pthread_create(t, NULL, routine, *(void **)&arg) == 0;
#endif
}

void pi_thread_join(pi_thread_t t)
{
#ifdef __WIN32
    WaitForSingleObject(t, INFINITE) == 0;
#else
    pthread_join(t, NULL) == 0;
#endif
}