#include <eloop.h>
#include <queue.h>
#include <stdlib.h>

struct eloop {
    queue_t * queue;
};

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

    goto init_return;

cleanup:
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

    if (eloop->queue)
    {
        queue_destroy(eloop->queue);
        eloop->queue = NULL;
    }
    
    free(eloop);
    return 0;
}

int eloop_add(eloop_t * eloop, event_t * event)
{
    if (!eloop || !eloop->queue)
    {
        return -1;
    }

    if (!event || !event->func || !event->data)
    {
        return -2;
    }

    queue_enqueue(eloop->queue, event);
    return 0;
}
// END OF SOURCE