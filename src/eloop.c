#include <eloop.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <queue.h>
#include <signal.h>

#define NUMBER_OF_THREADS 10
volatile sig_atomic_t exit_flag = 0;

struct eloop {
    queue_t * queue;
    pthread_t worker;
    pthread_cond_t cond;
    pthread_mutex_t lock;
};

static void * work_function(void * data);

eloop_t * eloop_create(void)
{
    eloop_t * new_eloop = calloc(1, sizeof(*new_eloop));

    if (!new_eloop)
    {
        goto init_return;
    }

    new_eloop->queue = queue_create(NULL, NULL);

    if (!new_eloop->queue)
    {
        goto cleanup;
    }

    new_eloop->cond = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    new_eloop->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    pthread_create(&(new_eloop->worker), NULL, work_function, new_eloop);

    goto init_return;

cleanup:
    queue_destroy(new_eloop->queue);
    new_eloop->queue = NULL;
    free(new_eloop);
    new_eloop = NULL;
init_return:
    return new_eloop;
}

int eloop_destroy(eloop_t * eloop)
{
    if (!eloop)
    {
        return -1;
    }

    event_t * event = NULL;
    exit_flag = 1;
    pthread_cond_broadcast(&(eloop->cond));
    pthread_join(eloop->worker, NULL);

    if (eloop->queue)
    {
        while(queue_get_size(eloop->queue))
        {
            event = queue_dequeue(eloop->queue);

            if (event->dfunc)
            {
                event->dfunc(event);
            }

            event = NULL;
        }

        queue_destroy(eloop->queue);
    }
    
    eloop->queue = NULL;
    free(eloop);
    return 0;
}

int eloop_add(eloop_t * eloop, event_t * event)
{
    if (!eloop || !(eloop->queue))
    {
        return -1;
    }

    if (!event || !event->efunc || !event->data)
    {
        return -2;
    }

    pthread_mutex_lock(&(eloop->lock));
    queue_enqueue(eloop->queue, event);
    pthread_cond_signal(&(eloop->cond));
    pthread_mutex_unlock(&(eloop->lock));
    return 0;
}

static void * work_function(void * data)
{
    if (!data)
    {
        return NULL;
    }

    eloop_t * eloop = (eloop_t *)data;

    for (;;)
    {
        pthread_mutex_lock(&(eloop->lock));

        while(queue_get_size(eloop->queue) == 0)
        {
            if (exit_flag)
            {
                pthread_mutex_unlock(&(eloop->lock));
                return NULL;
            }

            pthread_cond_wait(&(eloop->cond), &(eloop->lock));
        }

        event_t * event = queue_dequeue(eloop->queue);
        pthread_mutex_unlock(&(eloop->lock));

        if (event)
        {
            event->efunc(event->data);

            if (event->dfunc)
            {
                event->dfunc(event);
            }
        }  
    }

    return NULL;
}
// END OF SOURCE