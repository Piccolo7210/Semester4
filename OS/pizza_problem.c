#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define NUM_STUDENTS 5
#define S 8  // Number of slices per pizza

// Shared variables
sem_t pizza;           // Semaphore representing available pizza slices
sem_t deliver;         // Semaphore for ordering a new pizza
int num_slices = 0;    // Number of pizza slices available
pthread_mutex_t mutex; // Mutex to protect num_slices

void* student(void* arg) {
    while (1) {
        sem_wait(&pizza); 
       // Try to pick up a piece of pizza
        pthread_mutex_lock(&mutex);
        
        
        if (num_slices > 0) {
            
            num_slices--; // Take a slice
            printf("Student %ld ate a slice. Remaining slices: %d\n", (long)arg+1, num_slices);
        }
        
        if (num_slices == 0) {
            printf("Student %ld ordered the pizza\n",(long)arg+1);
            sem_post(&deliver); // Signal to order a new pizza
        }
        
        pthread_mutex_unlock(&mutex);
        
        // Simulate studying
        sleep(1);
    }
    return NULL;
}

void* delivery(void* arg) {
    while (1) {
        sem_wait(&deliver); // Wait for the signal to deliver pizza
        pthread_mutex_lock(&mutex);
        
        printf("Pizza delivery in progress...\n");
        num_slices = S; // Prepare a new pizza with S slices
        printf("New pizza delivered with %d slices\n", S);
        
        for (int i = 0; i < S; i++) {
            sem_post(&pizza); // Release each slice as available
        }
        
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t students[NUM_STUDENTS];
    pthread_t delivery_thread;

    // Initialize semaphores and mutex
    sem_init(&pizza, 0, 0);      // Initially no pizza slices available
    sem_init(&deliver, 0, 1);    // Allow one delivery order at the beginning
    pthread_mutex_init(&mutex, NULL);

    // Create student threads
    for (long i = 0; i < NUM_STUDENTS; i++) {
        pthread_create(&students[i], NULL, student, (void*)i);
    }

    // Create delivery thread
    pthread_create(&delivery_thread, NULL, delivery, NULL);

    // Join threads (not necessary in this infinite loop scenario)
    for (int i = 0; i < NUM_STUDENTS; i++) {
        pthread_join(students[i], NULL);
    }
    pthread_join(delivery_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&pizza);
    sem_destroy(&deliver);
    pthread_mutex_destroy(&mutex);

    return 0;
}
