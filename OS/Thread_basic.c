#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int sum;
void *runner(void *param);
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
int main(int argc, char *argv[]){
	pthread_t tid[5];
	pthread_attr_t attr;
	int num;
	printf("Argc value is = %d\n",argc);
	if(argc!=2){
		fprintf(stderr,"Argument number doesn't match\n");
		exit(1);
	}
	if(atoi(argv[1])<0){
		fprintf(stderr,"Argument %d must be non negative.\n",atoi(argv[1]));
		exit(1);
	}
	pthread_attr_init(&attr);
	num=atoi(argv[1]);
	for(int i =0; i<5;i++){
		int x=num+i;
		pthread_create(&tid[i],&attr,runner,&x);
		pthread_join(tid[i],NULL);
		fprintf(stdout,"Sum is  = %d \n",sum);
		
	}
	return 0;
}
void *runner(void *param){
sum=0;
int i,upper = *(int*)param;
	if(upper>0){
		for(i=1;i<=upper;i++){
			sum+=i;
		}
	}
	pthread_exit(0);
}
