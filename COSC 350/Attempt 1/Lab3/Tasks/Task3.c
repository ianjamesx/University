#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){

  char *infile = "foo", *outfile = "clone2";
  int filedes[2];

  //open up foo file to read from
  filedes[0] = open(infile, O_RDONLY);
  if(filedes[0] == -1){
    printf("Can't open input file\n");
    return 0;
  }

  //open up clone1 file, we will want read/write/execute on users, groups
  umask(0);
  filedes[1] = open(outfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP);

  printf("Opened files with filedes: %d, %d\n", filedes[0], filedes[1]);

  //create buffer to hold one char (one byte)
  char buffer[32];
  while (read(filedes[0], buffer, 32) > 0){
    //printf("reading: %d, %s\n", 32, buffer);
    //write to clone1
    write(filedes[1], buffer, 32);
  }

  close(filedes[0]);
  close(filedes[1]);

  return 0;

}
