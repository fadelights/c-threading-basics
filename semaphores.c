#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 6

sem_t demo_sem;

void* f(void* id);


int main() {
    pthread_t tid[THREAD_NUM];

    sem_init(&demo_sem, 0, 2);

    for (int i = 0; i < THREAD_NUM; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&tid[i], NULL, &f, (void*) id);
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        pthread_join(tid[i], NULL);
    }

    sem_destroy(&demo_sem);

    return 0;
}


void* f(void* id) {
    sem_wait(&demo_sem);

    sleep(1);
    printf("Greetings from thread %d.\n", *((int*) id));
    free(id);

    sem_post(&demo_sem);

    return NULL;
}
