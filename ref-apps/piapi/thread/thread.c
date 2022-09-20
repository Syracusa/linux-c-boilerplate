/* https://man7.org/linux/man-pages/man3/pthread_create.3.html */
#include "piapi.h"
#include <ctype.h>
#define handle_error_en(en, msg) \
    do                           \
    {                            \
        errno = en;              \
        perror(msg);             \
        exit(EXIT_FAILURE);      \
    } while (0)

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

struct thread_info
{                        /* Used as argument to thread_start() */
    pi_thread_t thread_id; /* ID returned by pthread_create() */
    int thread_num;      /* Application-defined thread # */
    char *argv_string;   /* From command-line argument */
};

/* Thread start function: display address near top of our stack,
   and return upper-cased copy of argv_string. */

static pi_thread_ret_t
thread_start(void *arg)
{
    struct thread_info *tinfo = arg;
    char *uargv;

    printf("Thread %d: top of stack near %p; argv_string=%s\n",
           tinfo->thread_num, (void *)&tinfo, tinfo->argv_string);

    uargv = strdup(tinfo->argv_string);
    if (uargv == NULL)
        handle_error("strdup");

    for (char *p = uargv; *p != '\0'; p++)
        *p = toupper(*p);

    return PI_THREAD_DONE;
}

int main()
{
    int s, opt, num_threads;

    num_threads = 10;

    /* Allocate memory for pthread_create() arguments. */

    struct thread_info *tinfo = calloc(num_threads, sizeof(*tinfo));
    if (tinfo == NULL)
        handle_error("calloc");

    /* Create one thread for each command-line argument. */

    for (int tnum = 0; tnum < num_threads; tnum++)
    {
        tinfo[tnum].thread_num = tnum + 1;

        static char args[10][100];
        sprintf(args[tnum], "Thread %d", tnum);
        tinfo[tnum].argv_string = args[tnum];

        /* The pthread_create() call stores the thread ID into
           corresponding element of tinfo[]. */
        pi_thread_create(&tinfo[tnum].thread_id,
                           &thread_start, &tinfo[tnum]);

        // s = pthread_create(&tinfo[tnum].thread_id, NULL,
        //                    &thread_start, &tinfo[tnum]);

    }

    /* Now join with each thread, and display its returned value. */

    for (int tnum = 0; tnum < num_threads; tnum++)
    {
        pi_thread_join(tinfo[tnum].thread_id);
        
        printf("Joined with thread %d;\n",
               tinfo[tnum].thread_num);
    }

    free(tinfo);
    exit(EXIT_SUCCESS);
}