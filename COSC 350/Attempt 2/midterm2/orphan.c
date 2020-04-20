#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid == 0){ //if child
        while(1); //just loop indefinetly
    } else {
        exit(0);
    }
}