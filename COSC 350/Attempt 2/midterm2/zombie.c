//program to create a zombie process in system

#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main(){

    pid_t pid = fork(); 

    // Parent process  
    if (pid > 0){
        sleep(10); 
    // Child process 
    } else {        
        exit(0); 
    }
    return 0; 
} 