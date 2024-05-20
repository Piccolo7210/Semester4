#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t mutex;
sem_t rwmutex;
int read_count=0;
#define reader_numebr 5
#define writer_numebr 2
void *reader(void *);
void *writer(void *);
int main()
{
    pthread_t readers[reader_numebr],writers[writer_numebr];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int readers_id[reader_numebr],writers_id[writer_numebr];
sem_init(&mutex,0,1);
sem_init(&rwmutex,0,1);
for(int i=0;i<reader_numebr;i++)readers_id[i]=i+1;
for(int i=0;i<writer_numebr;i++)writers_id[i]=i+1;

for(int i=0;i<reader_numebr;i++){
    pthread_create(&readers[i],&attr,reader,&readers_id[i]);
}
for(int i=0;i<writer_numebr;i++){
    pthread_create(&writers[i],&attr,writer,&writers_id[i]);
}
for(int i=0;i<reader_numebr;i++)pthread_join(readers[i],NULL);
for(int i=0;i<writer_numebr;i++)pthread_join(writers[i],NULL);
sem_destroy(&mutex);
sem_destroy(&rwmutex);


}
void *reader(void *p)
{
    int num=*(int*)p;
    while(1){
        sem_wait(&mutex);
read_count++;
if(read_count==1) sem_wait(&rwmutex);
sem_post(&mutex);
printf("Reader: %d is Reading\n",num);
sem_wait(&mutex);
printf("Reader: %d Completed Reading\n",num);
read_count--;
if(read_count==0) 
{
    sem_post(&rwmutex);
    printf("reader count is 0\n");
}
sem_post(&mutex);
sleep(3);
}

}

void *writer(void *p)
{
    int  num=*(int*)p;
    while(1)
    {
    printf("Writer %d: is about to start \n",num);
    sem_wait(&rwmutex);
    printf("Writer %d is writing\n",num);
    sem_post(&rwmutex);
    sleep(1);
    }
    

}
