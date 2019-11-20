/* holder.h */

#include <stdbool.h>
#include <pthread.h>
#include <scheduling.h>

#ifndef HOLDER_H
#define HOLDER_H

typedef struct holder_t holder_t;
struct holder_t {
    pthread_t   thread;
    tprio_t     prio;
    holder_t    *next;
};

extern int      count_holders(holder_t *);
extern bool     exists_holder(holder_t *, holder_t);
extern void     insert_holder(holder_t *, holder_t);
extern void     remove_holder(holder_t *, holder_t);
extern tprio_t  get_max_prio(holder_t *);
extern tprio_t  get_min_prio(holder_t *);
extern void     set_holders_prio(holder_t *, tprio_t);
extern tprio_t  get_holders_prio(holder_t *, holder_t);

#define max_prio(x,y) ((x) >= (y)) ? (x) : (y)
#define min_prio(x,y) ((x) <= (y)) ? (x) : (y)

#endif
