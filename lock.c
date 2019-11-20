/* lock.c */

#include <pthread.h>
#include <lock.h>
#include <holder.h>
#include <scheduling.h>

bool lock_create(lock_t *lock) {
    if (lock == NULL) {
        return false;
    }
    pthread_mutex_init(&lock->mutex, NULL);
    pthread_cond_init(&lock->cond, NULL);
    lock->readers = NULL;
    lock->writers = NULL;
    lock->lprio = 0;
    lock->lstate = FREE;
    return true;
}

bool lock(lock_t *lock, lstate_t type) {
    if (isbadtype(type)) {
        return false;
    }
    holder_t holder;
    holder.thread = curr_thread();
    holder.prio = get_prio(curr_thread());
    pthread_mutex_lock(&lock->mutex);
    if (exists_holder(lock->readers, holder) || exists_holder(lock->writers, holder)) {
        pthread_mutex_unlock(&lock->mutex);
        return false;
    }
    if (holder.prio > lock->lprio) {
        lock->lprio = holder.prio;
        set_holders_prio(lock->readers, lock->lprio);
        set_holders_prio(lock->writers, lock->lprio);
    }
    switch (type) {
        case READ:
            while (count_holders(lock->writers) > 0) {
                pthread_cond_wait(&lock->cond, &lock->mutex);
            }
            insert_holder(lock->readers, holder);
            printf("added reader. - %d\n", count_holders(lock->readers));
            lock->lstate = READ;
            break;
        case WRITE:
            while (count_holders(lock->writers) > 0 || count_holders(lock->readers) > 0) {
                pthread_cond_wait(&lock->cond, &lock->mutex);
            }
            insert_holder(lock->writers, holder);
            printf("added writer. - %d\n", count_holders(lock->writers));
            lock->lstate = WRITE;
            break;
        default:
            break;
    }
    if (lock->lprio > holder.prio) {
        set_prio(holder.thread, lock->lprio);
    }
    pthread_mutex_unlock(&lock->mutex);
    return true;
}

bool try_lock(lock_t *descriptor, lstate_t type) {
    switch (type) {
        case READ:
            if (descriptor->lstate == READ || descriptor->lstate == FREE) {
                return lock(descriptor, type);
            } else {
                return false;
            }
        case WRITE:
            if (descriptor->lstate == FREE) {
                return lock(descriptor, type);
            } else {
                return false;
            }
        default:
            return false;
    }
}

bool unlock(lock_t *lock) {
    holder_t holder;
    holder.thread = curr_thread();
    pthread_mutex_lock(&lock->mutex);
    if (!exists_holder(lock->readers, holder) && !exists_holder(lock->writers, holder)) {
        pthread_mutex_unlock(&lock->mutex);
        return false;
    }
    if (exists_holder(lock->readers, holder)) {
        holder.prio = get_holders_prio(lock->readers, holder);
        remove_holder(lock->readers, holder);
        if (count_holders(lock->readers) == 0) {
            lock->lstate = FREE;
            pthread_cond_signal(&lock->cond);
        }
    }
    if (exists_holder(lock->writers, holder)) {
        holder.prio = get_holders_prio(lock->writers, holder);
        remove_holder(lock->writers, holder);
        if (count_holders(lock->writers) == 0) {
            lock->lstate = FREE;
            pthread_cond_signal(&lock->cond);
        }
    }
    if (holder.prio != lock->lprio) {
        set_prio(holder.thread, holder.prio);
    } 
    lock->lprio = max_prio(get_max_prio(lock->readers), get_max_prio(lock->writers));
    set_holders_prio(lock->readers, lock->lprio);
    set_holders_prio(lock->writers, lock->lprio);
    pthread_mutex_unlock(&lock->mutex);
    return true;
}

bool lock_delete(lock_t *lock) {
    return false;
}
