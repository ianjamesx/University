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
    printf("Usage: ./child  [message] [nc] [tc]\n");
    return 0;
  }

  char *message = argv[1];
  int nc = stringtoint(argv[2]),
      tc = stringtoint(argv[3]);

  //output for each process

  for(; nc > 0; nc--){
    printf("%s  pID: %d\n", message, getpid());
    sleep(tc);
  }

  return 0;

}