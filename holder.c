/* holder.c */

#include <stdlib.h>
#include <holder.h>
#include <scheduling.h>

int count_holders(holder_t *handle) {
    holder_t *ptr = handle;
    int count = 0;
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    return count;
}

bool exists_holder(holder_t *handle, holder_t holder) {
    holder_t *ptr = handle;
    while (ptr != NULL) {
        if (ptr->thread == holder.thread) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

void insert_holder(holder_t *handle, holder_t holder) {
    holder_t *new_holder = malloc(sizeof(holder_t));
    new_holder->thread = holder.thread;
    new_holder->prio = holder.prio;
    new_holder->next = handle;
    handle = new_holder;
}

void remove_holder(holder_t *handle, holder_t holder) {
    holder_t *ptr = handle, *temp;
    if (ptr != NULL && ptr->thread == holder.thread) {
        handle = handle->next;
        free(ptr);
        return;
    }
    while (ptr != NULL && ptr->thread != holder.thread) {
        temp = ptr;
        ptr = ptr->next;
    }
    if (ptr == NULL) return;
    temp->next = ptr->next;
    free(ptr);
}

tprio_t get_max_prio(holder_t *handle) {
    holder_t *ptr = handle;
    tprio_t max = -9999;
    while (ptr != NULL) {
        if (ptr->prio > max) {
            max = ptr->prio;
        }
        ptr = ptr->next;
    }
    return max;
}

tprio_t get_min_prio(holder_t *handle) {
    holder_t *ptr = handle;
    tprio_t min = 9999;
    while (ptr != NULL) {
        if (ptr->prio < min) {
            min = ptr->prio;
        }
        ptr = ptr->next;
    }
    return min;
}

void set_holders_prio(holder_t *handle, tprio_t prio) {
    holder_t *ptr = handle;
    while (ptr != NULL) {
        set_prio(ptr->thread, prio);
        ptr = ptr->next;
    }
}

tprio_t get_holders_prio(holder_t *handle, holder_t holder) {
    holder_t *ptr = handle;
    while (ptr != NULL) {
        if (ptr->thread == holder.thread) {
            return ptr->prio;
        }
        ptr = ptr->next;
    }
    return (tprio_t)0;
}
