#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void stringreset(char *s){
 int i = 0;
 while(s[i] != '\0'){

   s[i] = 0;
   i++;
 }

}

char* getFileName(char *dir){

 int i = 0, j = 0;

 char *filename = malloc(PATH_MAX);

 while(dir[i]!='\0'){

   if(dir[i]=='/'){ //we hit a directory

    if(dir[i+1]=='\0'){ //end of string
      break;
    }

     stringreset(filename); //reset string
     j = 0; //set size to 0

   } else {

     filename[j] = dir[i];
     j++;

   }
   i++;
 }

 return filename;
}

int main(int argc, char **argv){

 if(argc < 3){
   printf("Usage: ./MyMv [inputdestination] [outputdestination]");
   return 0;
 }
 //Verify the input file exists.
 if(access(argv[1], F_OK) == -1){
   printf("Err, could not open input file\n");
   return 0;
 }

 //Check if the output is a directory
 struct stat sbuf;
 stat(argv[2], &sbuf);

 if(S_ISDIR(sbuf.st_mode)){

   //create a buffer to just the filename
   char b[PATH_MAX];
   char *filename = getFileName(argv[1]);
   sprintf(b, "%s/%s", argv[2], filename);

   link(argv[1], b);
   unlink(argv[1]);

 } else {

   //output is not a directory
   //simpler case, just link the two arguments
   link(argv[1], argv[2]);
   unlink(argv[1]);

 }

 return 0;
}
