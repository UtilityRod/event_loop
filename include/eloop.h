#ifndef _ELOOP_H_
#define _ELOOP_H_

typedef struct eloop eloop_t;

typedef int event_func(void * data);

typedef struct {
    void * data;
    event_func * func;
    
} event_t;

eloop_t * eloop_create(void);
int eloop_destroy(eloop_t * eloop);
int eloop_add(eloop_t * eloop, event_t * event);

#endif