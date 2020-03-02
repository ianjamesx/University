/* program testlseek.c */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

void appendtofileReverse(int[], int[], int, int, int);
void closefiles(int[], int);

int main(){

  int buffersize = 1; //we'll copy byte by byte

  //open foo
  int filedes[2], offset[2]; //two offsets will be needed
  if((filedes[0] = open("foo", O_RDONLY)) < 0){
    printf("Creat File Open Error On foo");
  }

  //open foo12
  umask(0);
  filedes[1] = open("foorev", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP);

  //use lseek to jump to end of file
  if((offset[0] = lseek (filedes[0], O_RDONLY, SEEK_END)) == -1){
    printf("Creat seekl Error");
  }

  //append contents of foo and foo1 to foo12
  appendtofileReverse(filedes, offset, 0, 1, buffersize);

  close(filedes, 2);

  //printf("offset = %d\n", offset[0]);
  return 0;

}

void appendtofileReverse(int filedes[], int offsets[], int currfile, int targetfile, int buffersize){

  char buffer[buffersize];
  //first, read last byte
  int i = 0, totaloffset = offsets[currfile];
  while (i <= totaloffset){

    //set from the start to the total offset minus the current iteration
    lseek(filedes[currfile], (totaloffset - i), SEEK_SET);
    read(filedes[currfile], buffer, buffersize);

    //write to clone
    write(filedes[targetfile], buffer, buffersize);

    i++;

  }

}

void closefiles(int filedes[], int fsize){

  int i;
  for(i = 0; i < fsize; i++){
    close(filedes[i]);
  }

}
