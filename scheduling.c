/* scheduling.c */

#include <pthread.h>
#include <sched.h>
#include <limits.h>
#include <scheduling.h>

pthread_t curr_thread() {
    return pthread_self();
}

tprio_t get_prio(pthread_t thread) {
    struct sched_param params;
    int policy;
    if (pthread_getschedparam(thread, &policy, &params) != 0) {
        return (tprio_t)INT_MIN;
    }
    /*
    if (policy != SCHED_POLICY) {
        return (tprio_t)INT_MIN;
    }
    */
    return (tprio_t)params.sched_priority;
}

tprio_t set_prio(pthread_t thread, tprio_t prio) {
    struct sched_param params;
    if (prio < sched_get_priority_min(SCHED_POLICY)) {
        prio = sched_get_priority_min(SCHED_POLICY);
    } else if (prio > sched_get_priority_max(SCHED_POLICY)) {
        prio = sched_get_priority_max(SCHED_POLICY);
    }
    params.sched_priority = prio;
    if (pthread_setschedparam(thread, SCHED_POLICY, &params) != 0) {
        return (tprio_t)INT_MIN;
    }
    return prio;
}
