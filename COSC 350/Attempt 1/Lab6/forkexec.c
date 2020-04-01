#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

  if(argc < 4){
    printf("Usage: ./fork [nc] [np] [tc] [tp]\n");
    return -1;
  }

  int nc = stringtoint(argv[1]);
  int np = stringtoint(argv[2]);
  int tc = stringtoint(argv[3]);
  int tp = stringtoint(argv[4]);

  pid_t pid;
  char *message;

  int exitcode;
  int slp;
  int n;

  printf("fork program starting\n");

  pid = fork();

  switch(pid){

    case -1:
      perror("fork failed");
    case 0:
      message = "This is the child";
      if(execlp("./child", message, argv[1], argv[3]) < 0){ //pass args from child to process image
        perror("execlp err: could not run child process"); //-1 status is an error
      }
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
