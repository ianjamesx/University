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
  int n, t;

  printf("fork program starting\n");

  pid = fork();

  switch(pid){

    case -1:
      printf("fork failed\n");
      exit(1);
    case 0:
      //message = "This is the child";
      if(execlp("./child", "This is the child", nc, tc) < 0){ //pass args from child to process image
        printf("execlp err: could not run child process\n"); //-1 status is an error
      }
    break;
    default:
      message = "This is the parent";
      n = np;
      t = tp;
    break;
  }

  for(; n > 0; n--) {
    printf("%s pid: %d\n", message, pid);
    sleep(t);
   }
  if(pid!=0){
    printf("Waiting for child to terminate\n");
    wait(0);
    printf("Child termated\n");
  }
  
  return 0;

}