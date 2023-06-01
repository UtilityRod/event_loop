#include <stdio.h>
#include <stdlib.h>
#include <eloop.h>

static int efunc(void * data);
static int dfunc(void * data);

int main(void)
{
    eloop_t * eloop = eloop_create();
    int * intptr = calloc(1, sizeof(*intptr));
    *intptr = 5;

    event_t * event = calloc(1, sizeof(*event));

    if (event)
    {
        event->data = intptr;
        event->efunc = efunc;
        event->dfunc = dfunc;
        eloop_add(eloop, event);
    }

    eloop_destroy(eloop);
}

static int efunc(void * data)
{
    if (!data)
    {
        return -1;
    }

    int * intptr = (int *)data;
    printf("Integer value: %d\n", *intptr);
}

static int dfunc(void * data)
{
    if (!data)
    {
        return -1;
    }

    event_t * event = (event_t *)data;
    free(event->data);

    event->dfunc = NULL;
    event->dfunc = NULL;
    event->data = NULL;
    free(event);
    return 0;
}