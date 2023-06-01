#include <stdio.h>
#include <stdlib.h>
#include <eloop.h>

static int efunc(void * data);
static int heap_dfunc(void * data);
static int stack_dfunc(void * data);

int main(void)
{
    eloop_t * eloop = eloop_create();
    int * intptr1 = calloc(1, sizeof(*intptr1));
    *intptr1 = 5;

    event_t * heap_event = calloc(1, sizeof(*heap_event));
    heap_event->data = intptr1;
    heap_event->efunc = efunc;
    heap_event->dfunc = heap_dfunc;
    eloop_add(eloop, heap_event);

    int * intptr2 = calloc(1, sizeof(*intptr2));
    *intptr2 = 10;

    event_t stack_event = {
        .data = intptr2,
        .efunc = efunc,
        .dfunc = stack_dfunc,
    };

    eloop_add(eloop, &stack_event);

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

static int heap_dfunc(void * data)
{
    if (!data)
    {
        return -1;
    }

    event_t * event = (event_t *)data;
    free(event->data);

    event->dfunc = NULL;
    event->efunc = NULL;
    event->data = NULL;
    free(event);
    return 0;
}

static int stack_dfunc(void * data)
{
    if (!data)
    {
        return -1;
    }

    event_t * event = (event_t *)data;
    free(event->data);

    event->dfunc = NULL;
    event->efunc = NULL;
    event->data = NULL;
    return 0;
}