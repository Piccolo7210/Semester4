#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
void *sum_calc(void* para);
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}
int sum=0;
int main(int argc, char *argv[]){
    int num,i;
    pthread_t thread[3];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
if(argc ==1 ){
printf("Give me the number.");
exit(0);
}
else{
num= atoi(argv[1]);
}
for(i=0;i<3;i++){
        char str[5];
		tostring(str,num+i);
pthread_create(&thread[i],&attr,sum_calc,str);
pthread_join(thread[i],NULL);
printf("Sum is %d\n",sum);
}
}
void* sum_calc(void*  para){
    sum=0;
    for(int i=1;i<=atoi(para);i++)sum+=i;
    pthread_exit(0);
}