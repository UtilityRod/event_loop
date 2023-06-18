#ifndef _ELOOP_H_
#define _ELOOP_H_

typedef struct eloop eloop_t;
typedef struct event event_t;
typedef int event_func_f(event_t * evet);

struct event {
    void * data;
    event_func_f * efunc;
};

eloop_t * eloop_create(void);
int eloop_destroy(eloop_t * eloop);
int eloop_add(eloop_t * eloop, event_t * event);

#endif