#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
	int n ;
	printf("Enter the value of n: ");
	scanf("%d",&n);
	int pid;
	pid=fork();
	int sum=0;
	if(pid==0){
		for(int i=0;i<=n;i++){
			
			if(i%2!=0){
				sum+=i;	
			}
		}
		printf("Child sum = %d\n",sum);
	}
	else if (pid>0){
	sum=0;
		for(int i=0;i<=n;i++){
			if(i%2==0)sum+=i;
		}
			printf("Parent sum = %d\n",sum);
	}
	else{
		printf("Error!\n");
	}
	return 0;
}



	

