#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

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

int isNumeric(char c){

  int lowerDigit = (int)'0',
      upperDigit = (int)'9';

  if((int)c >= lowerDigit && (int)c <= upperDigit){
    return 1;
  }

  return 0;

}

int main(int argc, char **argv){

  //umask(0);

  if(argc != 2){

    printf("Error, please input a file name\n");
    exit(1);

  }

  int infile, childout, parentout;

  if((infile = open(argv[1], O_RDONLY) < 0)){
    printf("Err, cannot open file\n");
    exit(1);
  }

  printf("%d\n", infile);

  int filesize = lseek (infile, O_RDONLY, SEEK_END);
  printf("filesize: %d\n", filesize);
  pid_t pid;
  pid = fork();

  char buffer;
  int i;

  int lowerDigit = '0',
      upperDigit = '9';

  switch(pid){

    case -1:
      perror("fork failed");
      exit(1);
    case 0:

    //child process

      if((childout = open("child.txt", O_WRONLY | O_CREAT, 0666) == -1)){
        printf("err, cannot open output child file\n");
        exit(1);
      }

      for(i = 0; i < filesize; i++){

        lseek(infile, (off_t)i, SEEK_SET);
        read(infile, &buffer, 1);
        if(isNumeric(buffer) == 0){
          printf("child: %c\n", buffer);
          write(childout, &buffer, 1);
        }
      }

    break;
    default:
      //parent process

      if((parentout = open("parent.txt", O_WRONLY | O_CREAT, 0666) == -1)){
        printf("err, cannot open output parent file\n");
        exit(1);
      }

      for(i = 0; i < filesize; i++){

        lseek(infile, (off_t)i, SEEK_SET);
        read(infile, &buffer, 1);
        if((int)buffer >= lowerDigit && (int)buffer <= upperDigit){
          printf("parent: %c\n", buffer);
          write(parentout, &buffer, 1);
        }
      }

    break;
  }

  exit(0);

}
