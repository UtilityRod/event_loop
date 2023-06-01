#include <eloop.h>
#include <stdlib.h>
#include <stdio.h>
#include <thread_pool.h>

#define NUMBER_OF_THREADS 10

struct eloop {
    thread_pool_t * pool;
};

static void * pool_func(void * data);

eloop_t * eloop_create(void)
{
    eloop_t * new_eloop = calloc(1, sizeof(*new_eloop));

    if (!new_eloop)
    {
        goto init_return;
    }

    new_eloop->pool = pool_create(NUMBER_OF_THREADS, pool_func);

    if (!(new_eloop->pool))
    {
        goto cleanup;
    }

    goto init_return;

cleanup:
    pool_destroy(new_eloop->pool);
    new_eloop->pool = NULL;
    free(new_eloop);
    new_eloop = NULL;
init_return:
    return new_eloop;
}

int eloop_destroy(eloop_t * eloop)
{
    if (eloop && eloop->pool)
    {
        pool_kill_all(eloop->pool);
        pool_destroy(eloop->pool);
        eloop->pool = NULL;
    }
    
    free(eloop);
    return 0;
}

int eloop_add(eloop_t * eloop, event_t * event)
{
    if (!eloop || !(eloop->pool))
    {
        return -1;
    }

    if (!event || !event->efunc || !event->data)
    {
        return -2;
    }

    pool_add_work(eloop->pool, event);

    return 0;
}

static void * pool_func(void * data)
{
    if (!data)
    {
        return NULL;
    }

    event_t * event = (event_t *)data;
    event->efunc(event->data);

    if (event->dfunc)
    {
        event->dfunc(event);
    }

    return NULL;
}
// END OF SOURCE