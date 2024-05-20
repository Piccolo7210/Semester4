#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>



sem_t forks[5];
pthread_t philosophers[5];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left_fork = id;
    int right_fork = (id + 1) % 5;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Hungry and trying to pick up forks
        printf("Philosopher %d is hungry.\n", id);

        // Pick up the forks
        if (id % 2 == 0) {
            sem_wait(&forks[left_fork]);
            printf("Philosopher %d picked up fork %d (left).\n", id, left_fork);
            sem_wait(&forks[right_fork]);
            printf("Philosopher %d picked up fork %d (right).\n", id, right_fork);
        } else {
            sem_wait(&forks[right_fork]);
            printf("Philosopher %d picked up fork %d (right).\n", id, right_fork);
            sem_wait(&forks[left_fork]);
            printf("Philosopher %d picked up fork %d (left).\n", id, left_fork);
        }

        // Eating
        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        // Put down the forks
        sem_post(&forks[left_fork]);
        printf("Philosopher %d put down fork %d (left).\n", id, left_fork);
        sem_post(&forks[right_fork]);
        printf("Philosopher %d put down fork %d (right).\n", id, right_fork);
    }

    free(num);
    return NULL;
}

int main() {
    for (int i = 0; i < 5; i++) {
        sem_init(&forks[i], 0, 1);
    }
    int id[5];
    for (int i = 0; i < 5; i++) {
        
        id[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < 5; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
