#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int openUtmpFile(){

  int fdes = open("/var/run/utmp", O_RDONLY);

  if(fdes < 0){
    printf("Unable to open utmp file\n");
    exit(-1);
  }

  return fdes;

}

int main(int argc, char **argv){

  int filedes = openUtmpFile();

  printf("Opened Utmp file\n");
  
  close(filedes);

  return 0;

}
