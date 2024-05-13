#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex;
sem_t rwmutex;
int read_count=0;

void *reader(void *);
void *writer(void *);
int main()
{
    pthread_t reader1,reader2,reader3,writer1;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
sem_init(&mutex,0,1);
sem_init(&rwmutex,0,1);
pthread_create(&reader1,&attr,reader,"1");
// printf("Hello\n");
pthread_create(&reader2,&attr,reader,"2");
// pthread_create(&reader3,&attr,reader,"3");

pthread_create(&writer1,&attr,writer,"1");
pthread_join(reader1,NULL);
pthread_join(reader2,NULL);
pthread_join(writer1,NULL);


}
void *reader(void *p)
{
sem_wait(&mutex);
read_count++;
if(read_count==1) sem_wait(&rwmutex);
sem_post(&mutex);
printf("Reader: %d is Reading\n",atoi(p));
sem_wait(&mutex);
printf("Reader: %d Completed Reading\n",atoi(p));
read_count--;
if(read_count==0) 
{
    sem_post(&rwmutex);
    printf("reader count is 0\n");
}
sem_post(&mutex);
}

void *writer(void *p)
{
printf("Writer is about to start \n");
sem_wait(&rwmutex);
printf("Writer %d is writingn ",atoi(p));
sem_post(&rwmutex);
}
