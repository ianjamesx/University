#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/*

minitest:
write two programs

*/

void ding();

int main(){

  pid_t pid;

  printf("sound the alarm\n");

  pid = fork();
  switch(pid){

    case -1:
      perror("fork failed");
      exit(1);
    break;
    case 0:
      //child
      sleep(5);
      kill(getppid(), SIGALARM);
      exit(0);
    break;

    default:

    break;
  }


}
