/* main.c */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <lock.h>
#include <scheduling.h>

lock_t rwlock;

void *reader(void *prio) {
    tprio_t thread_prio = (int)prio;
    printf("setting reader priority - %d\n", thread_prio);
    if (set_prio(curr_thread(), thread_prio) != thread_prio) {
        printf("unable to set reader priority\n");
        return NULL;
    }
    printf("reader acquiring lock...\n");
    lock(&rwlock, READ);
    printf("reader acquired lock.\n");
    sleep(3);
    printf("reader releasing lock...\n");
    unlock(&rwlock);
    printf("reader released lock.\n");
    return NULL;
}

void *writer(void *prio) {
    tprio_t thread_prio = (int)prio;
    printf("setting writer priority - %d\n", thread_prio);
    if (set_prio(curr_thread(), thread_prio) != thread_prio) {
        printf("unable to set writer priority\n");
        return NULL;
    }
    printf("writer acquiring lock...\n");
    lock(&rwlock, WRITE);
    printf("writer acquired lock.\n");
    sleep(3);
    printf("writer releasing lock...\n");
    unlock(&rwlock);
    printf("writer released lock.\n");
    return NULL;
}

int main(void) {
    pthread_t reader_t, another_reader_t, writer_t, another_writer_t;
    printf("initializing lock.\n");
    lock_create(&rwlock);
    printf("starting simulation.\n");
    pthread_create(&reader_t, NULL, reader, (void *)30);
    pthread_create(&another_reader_t, NULL, reader, (void *)25);
    pthread_create(&writer_t, NULL, writer, (void *)50);
    pthread_create(&another_writer_t, NULL, writer, (void *)70);
    pthread_join(reader_t, NULL);
    pthread_join(another_reader_t, NULL);
    pthread_join(writer_t, NULL);
    pthread_join(another_writer_t, NULL);
    printf("simulation ended.\n");
    exit(EXIT_SUCCESS);
}
