/* using signal and kill system calls
 * Write a compelte C program in which two children processes send signal to the parent. The first child send message SIGUSR1 to the parent and hte parent process responds by writing message "Hi Honey! Anything wrong?". The second child send message SIGUSR2 to the parent and the parent response by writing message "Do you make trouble again?".
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void handler(int sig){
  if(sig==SIGUSR1)
    printf("Hi Honey! Anything wrong?\n");
  else if(sig==SIGUSR2)
    printf("Do you make trouble again?\n");
}

int main(){
  signal(SIGUSR1, handler);
  signal(SIGUSR2, handler);

  pid_t c1 = fork(), c2;
  if(c1 == 0){

  }
  else {
    c2 = fork();
    if(c2 == 0){

    }
    else {
      kill(c1, SIGUSR1);
      kill(c2, SIGUSR2);
    }
  }
  wait(NULL);
  wait(NULL);
  return 0;
}
