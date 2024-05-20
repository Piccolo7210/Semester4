#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main(){
    char *args[] = {"./hello","Hiiiiiiieeee",NULL};
    printf("About to run HEllo\n");
    execvp(args[0], args);
    perror("execvp");
    exit(1);
}
