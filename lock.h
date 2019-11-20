/* lock.h */

#include <stdbool.h>
#include <pthread.h>
#include <holder.h>
#include <scheduling.h>

#ifndef LOCK_H
#define LOCK_H

typedef enum lstate {FREE, READ, WRITE} lstate_t;

typedef struct {
    lstate_t            lstate;
    tprio_t             lprio;
    holder_t            *readers;
    holder_t            *writers;
    pthread_cond_t      cond;
    pthread_mutex_t     mutex;
} lock_t;

extern bool lock_create(lock_t *);
extern bool lock(lock_t *, lstate_t);
extern bool try_lock(lock_t *, lstate_t);
extern bool unlock(lock_t *);
extern bool lock_destroy(lock_t *);

#define isbadtype(type) (type != READ && type != WRITE)

#endif
