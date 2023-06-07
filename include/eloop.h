#ifndef _ELOOP_H_
#define _ELOOP_H_

typedef struct eloop eloop_t;

typedef int event_func_f(void * data);

typedef struct {
    void * data;
    event_func_f * efunc;
    event_func_f * dfunc;
} event_t;

eloop_t * eloop_create(void);
int eloop_destroy(eloop_t * eloop);
int eloop_add(eloop_t * eloop, event_t * event);

#endif