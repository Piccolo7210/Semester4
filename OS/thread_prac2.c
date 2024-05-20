#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
void* runner(void* para);
int main(){
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int num=1000;
    pthread_create(&tid,&attr,runner,&num);
    pthread_join(tid,NULL);
}
void* runner(void*  para){
    printf("%d\n", *(int*)para);
    pthread_exit(0);
}