#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

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
  int n;

  if(argc < 3){
    printf("Not enough arguments, please input four integers\n");
    return 0;
  }

  char *message = argv[0];
  int nc = stringtoint(argv[1]),
      tc = stringtoint(argv[2]);

  //output for each process

  for(; nc > 0; nc--){
    printf("%s  pID: %d\n", message, getpid());
    sleep(tc);
  }

  exit(0);

}
