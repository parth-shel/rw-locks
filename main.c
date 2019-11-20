/* main.c */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <lock.h>
#include <scheduling.h>

lock_t rwlock;

void *reader() {
    printf("reader acquiring lock...\n");
    lock(&rwlock, READ);
    printf("reader acquired lock.\n");
    sleep(5);
    printf("reader releasing lock...\n");
    unlock(&rwlock);
    printf("reader released lock.\n");
    return NULL;
}

void *writer() {
    printf("writer acquiring lock...\n");
    lock(&rwlock, WRITE);
    printf("writer acquired lock.\n");
    sleep(5);
    printf("writer releasing lock...\n");
    unlock(&rwlock);
    printf("writer released lock.\n");
    return NULL;
}

int main(void) {
    pthread_t reader_t, writer_t;
    printf("initializing lock.\n");
    lock_create(&rwlock);
    printf("starting simulation.\n");
    pthread_create(&reader_t, NULL, reader, NULL);
    pthread_create(&writer_t, NULL, writer, NULL);
    pthread_join(reader_t, NULL);
    pthread_join(writer_t, NULL);
    printf("simulation ended.\n");
    exit(EXIT_SUCCESS);
}
