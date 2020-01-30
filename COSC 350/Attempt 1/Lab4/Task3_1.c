
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void closefiles(int filedes[], int fsize){

  int i;
  for(i = 0; i < fsize; i++){
    close(filedes[i]);
  }

}

int main(){

  umask(0);

  //manually set directory paths
  char *dirpath1 = "/mnt/linuxlab/home/ithomas3/Dir1";
  char *dirpath2 = "/mnt/linuxlab/home/ithomas3/Dir2";
  char *dirpath21 = "/mnt/linuxlab/home/ithomas3/Dir2/Dir21";

  //then, manually create each directory

  if(mkdir(dirpath1, 0777) < 0){
    printf("mkdir err\n");
  }

  if(mkdir(dirpath2, 0777) < 0){
    printf("mkdir err\n");
  }

  if(mkdir(dirpath21, 0777) < 0){
    printf("mkdir err\n");
  }

  //open files
  //copy hello to ~/dir2/dir21

  int filedes[2];

  char *originalpath = "/mnt/linuxlab/home/ithomas3/hello";
  char *copypath = "/mnt/linuxlab/home/ithomas3/Dir2/Dir21/hello";

  filedes[0] = open(originalpath, O_RDONLY);
  filedes[1] = open(copypath, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  if(filedes[0] < 0){
    printf("Err: cannot read input file\n");
    return 0;
  }

  //Create output file as executable, read, write for all.
  if(filedes[1] < 0){
    printf("Err: cannot open output file path\n");
    closefiles(filedes, 1);
    return 0;
  }

  printf("Files opened with fildes: %d, %d\n", filedes[0], filedes[1]);

  //copy content of hello to new location for hello
  char buffer[1];
  int nread;
  while ((nread = read(filedes[0], buffer, 1) > 0)){
    //printf("reading: %d, %c\n", nread, buffer[0]);
    //write to clone1
    write(filedes[1], buffer, nread);
  }

  closefiles(filedes, 2);

  //Create symbolic links.

  if(symlink("/mnt/linuxlab/home/ithomas3/Dir2/Dir21", "/mnt/linuxlab/home/ithomas3/Dir1/toDir21") < 0){
    printf("Symlink err\n");
  }

  if(symlink("/mnt/linuxlab/home/ithomas3/Dir2/Dir21/hello", "/mnt/linuxlab/home/ithomas3/Dir1/toHello") < 0){
    printf("Symlink err\n");
  }

  return 0;

}
