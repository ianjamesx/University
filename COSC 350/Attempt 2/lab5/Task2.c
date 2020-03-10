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

  struct utmp b;
  int loginNum = 0;

  while(read(filedes, &b, sizeof(b))){

    if(b.ut_type==7){
      loginNum++;
    }

    printf("Username: %s\n", b.ut_user);

  }

  printf("number of users found: %d\n", loginNum);
  close(filedes);

  return 0;

}
