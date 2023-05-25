#include <stdio.h>
#include <eloop.h>

static int test_func(void * data);

int main(void)
{
    eloop_t * eloop = eloop_create();
    int test_int = 2;

    event_t event = {
        .data = &test_int,
        .func = test_func,
    };

    eloop_add(eloop, &event);
    eloop_destroy(eloop);
}

static int test_func(void * data)
{
    int * int_ptr = (int *)data;
    printf("Integer value: %d\n", *int_ptr);
}