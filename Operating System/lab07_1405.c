#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int c_point;
int t_point;
void *runner(void *param);
int main(){
    int num = 10000;
    pthread_t  tid[100];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for(int i=0;i<100;i++){
    pthread_create(&tid[i],&attr,runner,&num);
	pthread_join(tid[i],NULL);
    }
    
    printf("Value of Pai = %lf\n",4.00*(c_point*1.00/t_point));
}
void *runner(void *param){
    int n = *(int *)param;
    srand(time(NULL));
    double radius = 1;
    for(int i=0;i<n;i++){
        
        double random_x = ((double)rand()/RAND_MAX)*2-1;
        double random_y = ((double) rand()/RAND_MAX)*2-1;
        double distance = sqrt((random_x*random_x+random_y*random_y));
        //printf("x = %lf y= %lf \n",random_x,random_y);
        if(distance>radius)t_point++;
        else {
            c_point++;
            t_point++;
        }
    }

}