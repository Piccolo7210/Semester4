#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#define BufferSize 5 

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void *producer(void *pno)
{   
    int item;
    while(1) {
        item = rand()/100; 
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d: produce Item %d index: %d\n", *((int *)pno),buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(3);
    }
}
void *consumer(void *cno)
{   
    while(1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d: Remove Item %d from: %d\n",*((int *)cno),item, out);
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(3);
    }
}

int main(int argc , char *argv[])
{   srand(time(NULL));

    pthread_t pro[atoi(argv[2])],con[atoi(argv[3])];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int p[atoi(argv[2])]; 
    int c[atoi(argv[3])];
    for(int i=0;i<atoi(argv[2]);i++){
        p[i]=i;
    }
for(int i=0;i<atoi(argv[3]);i++){
        c[i]=i;
    }
    for(int i = 0; i < atoi(argv[2]); i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&p[i]);
       
    }
    
    for(int i = 0; i < atoi(argv[3]); i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&c[i]);

    }

    for(int i = 0; i < 5; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(con[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}