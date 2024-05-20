#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 5

int readcount = 0;
int writecount = 0;

sem_t rmutex, wmutex, readTry, resource; // (initial value = 1)

void *reader(void *);
void *writer(void *);

int main() {
  pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
  int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
  pthread_attr_t attr;

  pthread_attr_init(&attr);

  sem_init(&rmutex, 0, 1);
  sem_init(&wmutex, 0, 1);
  sem_init(&readTry, 0, 1);
  sem_init(&resource, 0, 1);

  for (int i = 0; i < NUM_READERS; i++) {
    reader_ids[i] = i + 1;
    pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
  }

  // Create writer threads
  for (int i = 0; i < NUM_WRITERS; i++) {
    writer_ids[i] = i + 1;
    pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
  }

  // Join reader threads
  for (int i = 0; i < NUM_READERS; i++) {
    pthread_join(readers[i], NULL);
  }

  // Join writer threads
  for (int i = 0; i < NUM_WRITERS; i++) {
    pthread_join(writers[i], NULL);
  }

  return 0;
}

void *reader(void *p) {
  int r_num = *(int *)p;

  while (1) {
    sem_wait(&readTry);
    printf("Reader: %d is Reading\n", r_num);

    sem_wait(&rmutex);
    readcount++;
    if (readcount == 1) {
      sem_wait(&resource); // First reader acquires resource
    }
    sem_post(&rmutex);

    sem_post(&readTry);

    printf("Reader: %d Completed Reading\n", r_num);

    sem_wait(&rmutex);
    readcount--;
    if (readcount == 0) {
      sem_post(&resource); // Last reader releases resource
    }
    sem_post(&rmutex);

    sleep(5);
  }
}

void *writer(void *p) {
  int num_w = *(int *)p;

  while (1) {
    sem_wait(&wmutex);

    // Ensure no readers are active and writer mutex is free
    if (readcount == 0) {
      sem_wait(&resource);
      writecount++;
      printf("Writer is at critical Section \n");
      sem_post(&wmutex);

      printf("Writer %d is writing\n", num_w);

      sem_wait(&wmutex);
      writecount--;
      sem_post(&resource);
      sem_post(&wmutex);
    } else {
      // Writer waits if readers are active
      sem_post(&wmutex);
      sleep(1); // Adjust sleep time as needed
    }

    sleep(5);
  }
}
