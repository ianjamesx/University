//child runs forever
//parent prints message 10 times
//parent sends signal to child to exit
//parent prints message 3 times

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void handler(int sig){
  if(sig == SIGUSR1){
    printf("Exit message from child\n");
    exit(0);
  }
}

int main(){
  
  int status = 0;

  pid_t pid = fork(), c2;
  if(pid == 0){ //child process

    signal(SIGUSR1, handler); //set signal handler in child

    while(1){
        printf("Message from Child\n");
        sleep(1);
    }

  } else if(pid > 0){ //parent process

      int i;
      for(i = 0; i < 4; i++){
        printf("Message from Parent\n");
        sleep(1);
      }

      kill(pid, SIGUSR1); //send signal to child

      for(i = 0; i < 3; i++){
        printf("Exit from parent\n");
        sleep(1);
      }

      exit(0);

  }

  return 0;
}