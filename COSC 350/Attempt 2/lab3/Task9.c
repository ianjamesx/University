#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int palin(int fd1, int fd2){

  int offset; //we need to get the offset first

  if((offset = lseek (fd2, O_RDONLY, SEEK_END)) == -1){
    printf("Creat seekl Error");
    return 0;
  }

  //printf("OFFSET %d\n", offset);

  char buffer[offset];
  read(fd1, buffer, offset);

  //printf("%s\n", buffer);

  int i;
  for(i = 0; i < offset; i++){
    //individually check each character in the buffer
    if(buffer[i] != buffer[(offset - 1) - i]){

      //printf("%c is not %c\n", buffer[i], buffer[offset - i]);
      return 0;
    }
  }

  return 1;
}


int main(int argc, char **argv){

  if(argc < 2){
    printf("Not enough parameters, exiting\n");
    return 0;
  }

  char *infile = argv[1];
  int filedes[2];

  filedes[0] = open(infile, O_RDONLY);
  if(filedes[0] == -1){
    printf("Can't open input file\n");
    return 0;
  }

  filedes[1] = open(infile, O_RDONLY);
  if(filedes[1] == -1){
    printf("Can't open input file\n");
  }

  if(palin(filedes[0], filedes[1]) == 1){
    printf("File content is a palindrome\n");
  } else {
    printf("File content is not a palindrome\n");
  }

  return 0;
}
