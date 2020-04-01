#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){

  if(argc < 2){
    printf("Usage: ./task5 [input]\n");
    return 0;
  }

  umask(0);

  char *infile = argv[1], *childout = "child.txt", *parentout = "parent.txt";
  int filedes, cdes, pdes; //file descripters

  //open up foo file to read from
  filedes = open(infile, O_RDONLY);
  if(filedes == -1){
    printf("Can't open input file\n");
    return 0;
  }

  //open up clone1 file, we will want read/write on users, groups, others
  cdes = open(childout, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  pdes = open(parentout, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

  int size = lseek(filedes, 0, SEEK_END); //size of file
  int offset1, offset2; //offsets for file

  //printf("Opened files with filedes: %d, %d, %d\n", filedes[0], filedes[1], filedes[2]);

  pid_t pid;
  pid = fork();

  char buffer[1];
   int i;
   for(i = 0; i < size; i++){

     if(pid == -1){
       printf("Fork failed, exiting\n");
       return 0;
     }
     else if(pid == 0){ //child process
       lseek(filedes, offset1, SEEK_SET);
       read(filedes, buffer, 1);
       write(cdes, buffer, 1);
       offset1++;
     } else { //parent process
       lseek(filedes, offset2, SEEK_SET);
       read(filedes, buffer, 1);
       write(pdes, buffer, 1);
       offset2++;
     }
   }

  close(filedes);
  close(cdes);
  close(pdes);

  return 0;

}