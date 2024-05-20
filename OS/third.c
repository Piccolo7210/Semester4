#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include<unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 5

int readcount = 0;

sem_t resource, rmutex, serviceQueue; // All semaphores initialized to 1

void *reader(void *);
void *writer(void *);

int main() {
  pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
  int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

  sem_init(&resource, 0, 1);
  sem_init(&rmutex, 0, 1);
  sem_init(&serviceQueue, 0, 1); // FIFO semaphore for fairness

  for (int i = 0; i < NUM_READERS; i++) {
    reader_ids[i] = i + 1;
    pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
  }

  for (int i = 0; i < NUM_WRITERS; i++) {
    writer_ids[i] = i + 1;
    pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
  }

  for (int i = 0; i < NUM_READERS; i++) {
    pthread_join(readers[i], NULL);
  }

  for (int i = 0; i < NUM_WRITERS; i++) {
    pthread_join(writers[i], NULL);
  }

  return 0;
}

void *reader(void *p) {
  int r_num = *(int *)p;

  while (1) {
    // ENTRY Section
    sem_wait(&serviceQueue); // Wait in line to be serviced (FIFO)
    sem_wait(&rmutex);        // Request exclusive access to readcount

    readcount++;             // Update count of active readers
    if (readcount == 1) {    // If I am the first reader
      sem_wait(&resource);   // Request resource access for readers (writers blocked)
    }

    sem_post(&serviceQueue); // Let next in line be serviced
    sem_post(&rmutex);        // Release access to readcount

    // CRITICAL Section
    printf("Reader: %d is Reading\n", r_num);
    sleep(1); // Simulate reading

    // EXIT Section
    sem_wait(&rmutex);        // Request exclusive access to readcount
    readcount--;             // Update count of active readers
    if (readcount == 0) {    // If there are no readers left
      sem_post(&resource);   // Release resource access for all
    }
    sem_post(&rmutex);        // Release access to readcount
  }
}

void *writer(void *p) {
  int num_w = *(int *)p;

  while (1) {
    // ENTRY Section
    sem_wait(&serviceQueue); // Wait in line to be serviced (FIFO)
    sem_wait(&resource);    // Request exclusive access to resource

    sem_post(&serviceQueue); // Let next in line be serviced

    // CRITICAL Section
    printf("Writer %d is writing\n", num_w);
    sleep(2); // Simulate writing

    // EXIT Section
    sem_post(&resource); // Release resource access for next reader/writer
  }
}
