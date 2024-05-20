#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define NUM_READERS 3
#define NUM_WRITERS 5
// DEADDlock kheye ache. Karon ber korte parsina
int readcount=0;
int writecount=0;                   //(initial value = 0)
sem_t rmutex, wmutex, readTry, resource; //(initial value = 1)
void *reader(void *);
void *writer(void *);
int main()
{
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
sem_init(&rmutex,0,1);
sem_init(&wmutex,0,1);
sem_init(&readTry,0,1);
sem_init(&readTry,0,1);

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


}
void *reader(void *p)
{
int r_num=*(int*)p;
while(1){
    sem_wait(&readTry);
    printf("Reader: %d is Reading\n",r_num);
sem_wait(&rmutex);
readcount++;
if(readcount==1) sem_wait(&resource);
sem_post(&readTry);
sem_post(&rmutex);
//sem_post(&readTry);
printf("Reader: %d Completed Reading\n",r_num);
sem_wait(&rmutex);
readcount--;
if(readcount==0) 
{
    sem_post(&resource);
    printf("reader count is 0\n");
}
sem_post(&rmutex);
sleep(5);
}
}
void *writer(void *p)
{
    int num_w= *(int*)p;
    while(1){
    sem_wait(&wmutex);
    
    writecount++;
    printf("Writer is at critical Section \n");
    if(writecount==1)sem_wait(&readTry);
    sem_wait(&resource);
    sem_post(&wmutex);
    
    //sem_wait(&resource);
    printf("Writer %d is writingn ",num_w);
    sem_post(&resource);
    sem_wait(&wmutex);
    writecount--;
    if(writecount == 0){
        sem_post(&readTry);
    }
    sem_post(&wmutex);
    sleep(5);
    }
}