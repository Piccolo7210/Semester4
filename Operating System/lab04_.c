#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(){
	int i,j,k,n;
	freopen("mat.txt","r",stdin);
	//printf("Enter the number of row and column for square matrix: ");
	scanf("%d",&n);
	int arr1[n][n],arr2[n][n],arr[n][n];
	//printf("Matrix 1 input:");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d",&arr1[i][j]);
		}
	}
	//printf("Matrix 2 input:");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%d",&arr2[i][j]);
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			arr[i][j]=0;
		}
	}
	int c=0;
	for(i=0;i<n;i++){
		int pid=fork();
		c++;
		if(pid==0){
			for(j=0;j<n;j++){
				for(k=0;k<n;k++){
					arr[i][j]+=arr1[i][k]*arr2[k][j];
				}
			}
			printf("Child %d:\n",c);
			for(int m=0;m<n;m++){
				printf("%d ",arr[i][m]);
			}
			printf("\n");
			exit(0);
		}
	}
}
