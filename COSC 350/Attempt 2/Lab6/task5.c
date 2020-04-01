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

  printf("INPUT IS %s", c);
  while(c[i] != '\0'){
    num = 10 * num + (c[i] - '0');
    i++;
  }
  printf("OUTPUT IS %d", num);
  return num;

}

int isNumeric(char c){

  int lowerDigit = '0',
      upperDigit = '9';

  if((int)c >= lowerDigit && (int)c <= upperDigit){
    return 1;
  }

  return 0;

}
/*
void parentHandler(){
  int parentout, infile;
  if((infile = open(argv[1], O_RDONLY) < 0)){
    printf("Err, cannot open file\n");
    exit(1);
  }
  if((parentout = open("parent.txt", O_WRONLY | O_CREAT, 0666) == -1)){
    printf("err, cannot open output parent file\n");
    exit(1);
  }
  while ((nread = read(infile, buffer, 1) > 0)){
    if(isNumeric(buffer[0]) == 1){
      write(parentout, buffer, nread);
    }
  }
}
*/
int main(int argc, char **argv){

  umask(0);

  if(argc != 2){
    printf("Usage: ./task5 [inputfile]\n");
    exit(1);
  }

  int infile, childout, parentout;

  if((infile = open(argv[1], O_RDONLY) < 0)){
    printf("Err, cannot open file\n");
    exit(1);
  }


  printf("%d\n", infile);

  //int filesize = lseek(infile, (off_t)0, SEEK_END);
  pid_t pid = 1;
  pid = fork();
  printf("Forked to id: %d\n", pid);

  char buffer[1];
  int nread;
  int i

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

     printf("child output file open, reading file\n");
    printf("READING FILE: %d", infile);
      while ((nread = read(infile, buffer, 1) > 0)){
          printf("child: %s", buffer);
        if(isNumeric(buffer[0]) == 0){
            printf("child in: %s", buffer);
          write(childout, buffer, nread);
        }
      }

      printf("Child process complete\n");

      //signal(SIGINT);

    break;
    default:

      //parent process

      //sighandler_t sig;
      //sig = signal(SIGINT, parentHandler);
      //pause();

      if((parentout = open("parent.txt", O_WRONLY | O_CREAT, 0666) == -1)){
        printf("err, cannot open output parent file\n");
        exit(1);
      }

      printf("parent output file open, reading file\n");

      printf("READING FILE: %d", infile);

      while ((nread = read(infile, buffer, 1) > 0)){
        if(isNumeric(buffer[0]) == 1){
          write(parentout, buffer, nread);
        }
      }

       printf("Parent process complete\n");

    break;
  }

  exit(0);

}