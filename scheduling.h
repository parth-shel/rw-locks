/* scheduling.h */

#include <pthread.h>

#ifndef SCHEDULING_H
#define SCHEDULIN_H

#define SCHED_POLICY SCHED_FIFO

typedef int tprio_t;

extern pthread_t curr_thread();
extern tprio_t get_prio(pthread_t);
extern tprio_t set_prio(pthread_t, tprio_t);

#endif
