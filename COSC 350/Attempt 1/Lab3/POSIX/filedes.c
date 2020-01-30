#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv){

  char *infile = "foo", *outfile = "clone1", *fileaux = "clone2";
  int codes[3];

  if (access(infile, F_OK) == 0) {
      codes[0] = open(infile, O_RDONLY);
  } else {
    codes[0] = open(infile, O_WRONLY|O_CREAT|O_SYNC, 0700);
  }

  if (access(outfile, F_OK) == 0) {
      codes[1] = open(outfile, O_RDONLY);
  } else {
      codes[1] = open(outfile, O_WRONLY|O_CREAT|O_SYNC, 0700);
  }

  if (access(fileaux, F_OK) == 0) {
      codes[2] = open(fileaux, O_RDONLY);
  } else {
      codes[2] = open(fileaux, O_WRONLY|O_CREAT|O_SYNC, 0700);
  }

  printf("%d, %d, %d\n", codes[0], codes[1], codes[2]);

  close(codes[0]);
  close(codes[1]);
  close(codes[2]);
  
}
