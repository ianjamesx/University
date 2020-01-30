/* program testlseek.c */
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

void appendtofile(int filedes[], int currfile, int targetfile, int buffersize){

  char buffer[buffersize];
  while (read(filedes[currfile], buffer, buffersize) > 0){
    //printf("reading: %d byte buffer, %s\n", buffersize, buffer);
    //write to clone1
    write(filedes[targetfile], buffer, buffersize);
  }

}

void closefiles(int filedes[], int fsize){

  int i;
  for(i = 0; i < fsize; i++){
    close(filedes[i]);
  }

}

int main(){

  int buffersize = 1; //we'll copy byte by byte

  //open foo and foo1
  int filedes[3], offset;
  if((filedes[0] = open("foo", O_RDONLY)) < 0){
    printf("Creat File Open Error On foo");
  }

  if((filedes[1] = open("foo1", O_RDONLY)) < 0){
    printf("Creat File Open Error On foo1");
  }

  //open foo12
  umask(0);
  filedes[2] = open("foo12", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP);

  //use lseek to jump to end of file
  if((offset = lseek (filedes[2], O_WRONLY | O_APPEND, SEEK_END)) == -1){
    printf("Creat seekl Error");
  }

  //append contents of foo and foo1 to foo12
  appendtofile(filedes, 0, 2, buffersize);
  appendtofile(filedes, 1, 2, buffersize);

  closefiles(filedes, 3);

  //printf("offset = %d\n", offset);
  return 0;

}
