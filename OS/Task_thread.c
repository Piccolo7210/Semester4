#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int max,avg,min;
int count=0;
void *runner(void *param);
int num;
int arr[20];
int main(int argc, char *argv[]){
	max=atoi(argv[1]);
	min=atoi(argv[1]);
	pthread_t tid[5];
	pthread_attr_t attr;
	
	num=argc-1;
	if(argc<2){
		fprintf(stderr,"Argument number doesn't match\n");
		exit(1);
	}
	pthread_attr_init(&attr);
		for(int i=0;i<num;i++)arr[i]=atoi(argv[i+1]);
	for(int i =1; i<=num;i++){
		pthread_create(&tid[i-1],&attr,runner,argv[i]);
		pthread_join(tid[i-1],NULL);
		
	}
	fprintf(stdout,"Max is  = %d \n",max);
	fprintf(stdout,"Average is  = %d \n",avg);
	fprintf(stdout,"Min is  = %d \n",min);
	return 0;
}
void *runner(void *param){
count++;
if(count==1){
int i,j;
for(i=0;i<num;i++){
	if(max<arr[i])
	{
		max = arr[i];
	}
}
	
	pthread_exit(0);
}
else if(count==2){
int i,j;
avg=0;
for(i=0;i<num;i++){
avg+=arr[i];
}	
avg/num;
	pthread_exit(0);
}
else if (count==3){
int i;
for(i=0;i<num;i++)
	if(min>arr[i])
	{
		min = arr[i];
	}
	pthread_exit(0);
}
	
	
}
