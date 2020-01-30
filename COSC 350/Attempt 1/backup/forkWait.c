#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

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
    printf("Not enough arguments, please input four integers\n");
    return 0;
  }

  int nc = stringtoint(argv[1]),
      np = stringtoint(argv[2]),
      tc = stringtoint(argv[3]),
      tp = stringtoint(argv[4]);

  printf("fork program starting\n");
  pid = fork();

  switch (pid) {
    case -1:
      perror("fork failed");
    break;
    case 0:
      message = "This is the child";
      n = nc;
    break;
    default:
      message = "This is the parent";
      n = np;
    break;
  }

  for(; n > 0; n--){
    puts(message);
    sleep(tc);
  }

  exit(0);

}
