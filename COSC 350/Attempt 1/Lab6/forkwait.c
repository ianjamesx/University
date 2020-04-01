#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/*

answer to question in lab:

this program differs from fork.c as the parent process idles
while it awaits the child process to finish, so all messages from
child "This is the child" proceed before the parents message outputs

*/

int stringtoint(char *c){

  //convert string to int
  int i = 0;
  long int num = 0;
  while(c[i] != '\0'){
    num = 10 * num + (c[i] - '0');
    i++;
  }

  return num;

}

int main(int argc, char **argv){

  pid_t pid;
  char *message;
  int n;

  if(argc < 4){
    printf("Usage: ./fork [nc] [np] [tc] [tp]\n");
    return 0;
  }

  int nc = stringtoint(argv[1]),
      np = stringtoint(argv[2]),
      tc = stringtoint(argv[3]),
      tp = stringtoint(argv[4]);

  int exitcode;
  int slp;

  printf("fork program starting\n");
  pid = fork();

  switch (pid) {
    case -1:
      perror("fork failed");
    break;
    case 0:
      message = "This is the child";
      n = nc;
      exitcode = 37;
      slp = tc;
    break;
    default:
      message = "This is the parent";
      n = np;
      exitcode = 0;
      slp = nc;
    break;
  }

  /*
  wait for child processes to finish before running parents
  we can do this by passing the parent's pid to wait()
  we should only get back child pid's, forcing parent processes
  to wait on childrens
  */
  for(; n > 0; n--) {
    puts(message);
    sleep(slp);
  }

  if(pid!=0){
    int stat_val;
    pid_t child_pid;

    child_pid = wait(&stat_val);

    printf("Child has finished: PID = %d\n", child_pid);

    if(WIFEXITED(stat_val)){
      printf("Child exited with code: %d\n", WEXITSTATUS(stat_val));
    } else {
      printf("Child terminated abnormally\n");
    }
  }

  exit(exitcode);

}