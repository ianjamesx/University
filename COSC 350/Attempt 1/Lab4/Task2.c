#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void closefiles(int filedes[], int fsize){

  int i;
  for(i = 0; i < fsize; i++){
    close(filedes[i]);
  }

}

int main(int argc, char **argv){

  if(argc < 3){
    printf("Not enough arguments, please input two file paths [source] [copy]\n");
    return 0;
  }

  char *infile = argv[1], *outfile = argv[2];
  int filedes[2];

  //open up foo file to read from
  filedes[0] = open(infile, O_RDONLY);
  if(filedes[0] == -1){
    printf("Can't open input file\n");
    return 0;
  }

  //open up clone1 file, we will want read/write on users, groups, others
  umask(0);
  filedes[1] = open(outfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  printf("Opened files with filedes: %d, %d\n", filedes[0], filedes[1]);

  //create buffer to hold one char (one byte)
  char buffer[1];
  int nread;
  while ((nread = read(filedes[0], buffer, 1) > 0)){
    //printf("reading: %d, %c\n", nread, buffer[0]);
    //write to clone1
    write(filedes[1], buffer, nread);
  }

  closefiles(filedes, 2);

  return 0;

}
