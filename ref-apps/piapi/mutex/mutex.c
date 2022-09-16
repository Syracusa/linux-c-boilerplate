#include "piapi.h"

int shared = 0;

pi_mutex_t * mt;

pi_thread_ret_t routine(void* arg){
    for (int i = 0; i < 10; i++){
        pi_mutex_lock(mt);
        shared++;
        pi_mutex_unlock(mt);
    }

    return PI_THREAD_DONE;
}

int main(){
    mt = pi_mutex_new();
    
    pi_thread_t t1, t2;
    pi_thread_create(&t1, routine, NULL);
    pi_thread_create(&t2, routine, NULL);
    
    pi_thread_join(t1);
    pi_thread_join(t2);

    printf("Res : %d\n", shared);
    pi_mutex_free(mt);
}