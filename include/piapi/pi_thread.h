#ifndef PI_THREAD_H
#define PI_THREAD_H

#ifdef __WIN32
typedef HANDLE pi_thread_t;
typedef unsigned long pi_thread_ret_t;

#define PI_THREAD_DONE 1
#define PI_THREAD_FAIL 0

#else
#include <pthread.h>
typedef unsigned long pi_thread_t;
typedef void* pi_thread_ret_t;

#define PI_THREAD_DONE NULL
#define PI_THREAD_FAIL NULL
#endif

typedef void pi_mutex_t;

pi_mutex_t *pi_mutex_new();

void pi_mutex_free(pi_mutex_t *mt);

void pi_mutex_lock(pi_mutex_t *mt);

void pi_mutex_unlock(pi_mutex_t *mt);

void pi_thread_create(pi_thread_t *t, pi_thread_ret_t routine(void *), void *arg);

void pi_thread_join(pi_thread_t t);


#endif