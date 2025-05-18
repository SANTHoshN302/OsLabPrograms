/* Write a C program to simulate: (Any one)
a) Producer-Consumer problem using semaphores. 
b) Dining-Philosopher’s problem */

// Producer-Consumer Problem in C using Semaphores

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1); 
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(2);
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

/* OUTPUT
Producer produced: 17
Consumer consumed: 17
Producer produced: 42
Producer produced: 33
Consumer consumed: 42
Producer produced: 91
Consumer consumed: 33
Producer produced: 27
Consumer consumed: 91
Producer produced: 84
Consumer consumed: 27
Consumer consumed: 84
Producer produced: 61
Producer produced: 73
Consumer consumed: 61
...
*/



// Dining Philosophers Problem in C using Semaphores

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t room;  

void* philosopher(void* num) {
    int id = *(int*)num;
    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 3);

        sem_wait(&room); 
        sem_wait(&forks[id]); 
        sem_wait(&forks[(id + 1) % N]); 

        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 2);

        sem_post(&forks[id]); 
        sem_post(&forks[(id + 1) % N]); 
        sem_post(&room); 

        printf("Philosopher %d is done eating.\n", id);
    }
}

int main() {
    pthread_t threads[N];
    int ids[N];

    sem_init(&room, 0, N - 1);  

    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&room);

    return 0;
}

/* OUTPUT
Philosopher 0 is thinking.
Philosopher 1 is thinking.
Philosopher 2 is thinking.
Philosopher 3 is thinking.
Philosopher 4 is thinking.
Philosopher 1 is eating.
Philosopher 1 is done eating.
Philosopher 2 is eating.
Philosopher 0 is eating.
Philosopher 0 is done eating.
Philosopher 2 is done eating.
Philosopher 4 is eating.
Philosopher 3 is eating.
Philosopher 4 is done eating.
Philosopher 3 is done eating.
Philosopher 1 is thinking.
...
*/

