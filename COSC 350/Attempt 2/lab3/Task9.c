#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int palin(int fd1, int fd2);
void closefiles(int[], int);

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

  filedes[1] = dup(filedes[0]);

  //printf("%d and %d\n", filedes[0], filedes[1]);

  if(palin(filedes[0], filedes[1]) == 1){
    printf("File content is a palindrome\n");
  } else {
    printf("File content is not a palindrome\n");
  }

  closefiles(filedes, 2);

  return 0;
}


int palin(int fd1, int fd2){

  char front, back; //buffers we need
  int first = 0, last = lseek(fd2, -1, SEEK_END); //offsets for reading

  //We can loop until we hit the mid point(first==last)
  //or until we encounter a mismatch.

  while(first < last){
    //Set seek to first offset and read into a buffer
    lseek(fd1, first, SEEK_SET);
    if(read(fd1, &front, 1) == -1){ //check for errs
      printf("read err front\n");
      return 0;
    }
    //Set seek to last offset and read into a buffer
    lseek(fd2, last, SEEK_SET);
    if(read(fd2, &back, 1) == -1){
      printf("read err back\n");
      return 0;
    }

    if(front != back || front == '\n' || back == '\n'){ //got a mismatch, return 0
      printf("mis-match found, %c != %c\n", front, back);
      return 0;
    }

    //move forward for first incrementor, back for last one
    first++;
    last--;

  }

  return 1; //if we get this far, we made it, file is palindrome, return 1

}

void closefiles(int filedes[], int fsize){
  int i;
  for(i = 0; i < fsize; i++){
    close(filedes[i]);
  }
}
