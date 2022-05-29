/* The producer-consumer solution written in C.

There are a few problems that need addressing:
    1. Managing shared memory
        Which we will handle using Mutex Locks
    2. Checking if buffer is full
        In which case the producer should go
        to sleep and be awakened by the
        consumer whenever the buffer has an
        empty slot -- solved by using semaphores
    3. Checking if buffer is empty
        In which case the consumer should go
        to sleep and be awakened by the
        producer whenever the buffer has an
        item inside -- solved by using semaphores

In this example, the producer is going to
generate random numbers in range GEN_RANGE
into the buffer which the consumer will consume.
Numbers will be consumed in a LIFO fashion.

Written by Arman Rezaei (9723034)
Amirkabir University of Technology
May 27, 2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>

#define THREAD_NUMS 4
#define BUFFER_SIZE 8

#define PROD_DURATION 2
#define CONS_DURATION 2
#define GEN_RANGE 128


// define the buffer and variables for managing it
int buffer[BUFFER_SIZE];
int buffer_index = 0;

pthread_mutex_t buffer_lock;

sem_t buff_sem_empty;
sem_t buff_sem_full;

// function signatures
void* producer(void*);
void* consumer(void*);
void sigint_handler();


int main() {
    printf("Program starting--press Ctrl+C to exit.\n");
    signal(SIGINT, sigint_handler);

    pthread_t tid[THREAD_NUMS];

    pthread_mutex_init(&buffer_lock, NULL);

    sem_init(&buff_sem_empty, 0, BUFFER_SIZE);
    sem_init(&buff_sem_full, 0, 0);

    // create threads
    for (int i = 0; i < THREAD_NUMS; i++) {
        if (i % 2 == 0)
            pthread_create(&tid[i], NULL, &producer, (void*) i);
        else
            pthread_create(&tid[i], NULL, &consumer, (void*) i);
    }

    // join threads
    for (int i = 0; i < THREAD_NUMS; i++)
        pthread_join(tid[i], NULL);

    pthread_mutex_destroy(&buffer_lock);

    sem_destroy(&buff_sem_empty);
    sem_destroy(&buff_sem_full);

    return 0;
}


void* producer(void* thread_index) {
    while (1) {
        // produce
        int x = rand() % GEN_RANGE;
        printf("(thread %d)\t %d was produced.\n", (int) thread_index, x);

        sem_wait(&buff_sem_empty); // wait until the buffer has at least one empty slot
        pthread_mutex_lock(&buffer_lock); // 🔒 lock the buffer 🔒

        // add to buffer
        buffer[buffer_index] = x;
        buffer_index += 1;

        pthread_mutex_unlock(&buffer_lock); // 🔓 unlock the buffer 🔓
        sem_post(&buff_sem_full); // signal addition of item

        // wait PROD_DURATION before producing any further
        sleep(PROD_DURATION);
    }
}

void* consumer(void* thread_index) {
    while (1) {
        sem_wait(&buff_sem_full); // wait until there is at least one element in the buffer
        pthread_mutex_lock(&buffer_lock); // 🔒 lock the buffer 🔒

        // get from buffer
        buffer_index -= 1;
        int x = buffer[buffer_index];

        pthread_mutex_unlock(&buffer_lock); // 🔓 unlock the buffer 🔓
        sem_post(&buff_sem_empty); // signal removal of item

        // consume
        printf("(thread %d)\t %d was consumed.\n", (int) thread_index, x);

        // wait CONS_DURATION before consuming any further
        sleep(CONS_DURATION);
    }
}

void sigint_handler() {
    printf("\nKeyboard interrupt--exiting.\n");
    exit(0);
}
