#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(){
    double x = ((double)rand() / (RAND_MAX + 1.0) * (1.0 - (-1.0)) - 1.0);
                                                    //(x-(-x) )-x
       srand(time(NULL));
    while(x<1 && x>-1){
        x = ((double)rand() / (RAND_MAX + 1.0) * (1.0 - (-1.0)) - 1.0);

        printf("%lf\n",x);
    }
}