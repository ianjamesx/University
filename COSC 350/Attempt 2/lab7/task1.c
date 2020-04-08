/* The BLP version of alarm.c uses the old-fashioned signal methodology. In this task, you will modify alarm.c to use sigaction.
 * A. Copy alarm.c from BLP4th edition page 485, page 468 in BLP 3rd edition.
 * B. Modify alarm.c so it uses sigaction
 */

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> //Contains memset

static int alarm_fired = 0;

void ding(int sig)
{
  alarm_fired = 1;
}

int main(){
  pid_t pid;

  printf("alarm application starting\n");
  pid = fork();
  switch(pid){
    case -1:
      /* Failure */
      perror("fork failed");
      exit(1);
    case 0:
      /* Child */
      sleep(5);
      kill(getppid(), SIGALRM);
      exit(0);
  }

  /* If we get here, we are the parent process */
  printf("Waiting for alarm to go off\n");
  struct sigaction act;
  memset(&act, 0, sizeof(act));
  act.sa_handler = ding;
  if(sigaction(SIGALRM,&act, 0)){
    perror("sigaction error\n");
    return -1;
  }

  pause();

  if(alarm_fired)
    printf("Ding!\n");

  printf("done\n");
  exit(0);
}
