#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void strReset(char word[], int strsize){
  int i;
  for(i = 0; i < strsize; i++){
    word[i] = '\0';
  }
}

void strResize(char *str){

  int i, strsize = strlen(str)-1;
  str[strsize-1] = '\0';
  /*
  for(i = strsize; i > 0; i--){
    printf("(%d %c)", (int)str[i], str[i]);
    if((int)str[i] == -1){
      str[i] = '\0';
      return;
    } else {
      str[i] = '\0';
    }
  }
  */
}

int main(int argc, char **argv){

  int filedes[1];

  filedes[0] = open("shadow.txt", O_RDONLY);
  printf("%d\n", filedes[0]);
  if(filedes[0] == -1){
    printf("Not happening...\n");
    return 0;
  }

  int shadowcount = 11;
  int hardsize = 50;

  char **allshadows = malloc(sizeof(char*) * shadowcount);
  char **allusers = malloc(sizeof(char*) * shadowcount);

  //create buffer to hold one char (one byte)
  char buffer[1];
  char currword[hardsize];
  int nread, currwordIndex = 0, ind = 0;
  while ((nread = read(filedes[0], buffer, 1) > 0)){

    if((int)buffer[0] == 58){ //:

      allusers[ind] = malloc(sizeof(char) * currwordIndex);
      strcpy(allusers[ind], currword);
      strReset(currword, currwordIndex);
      currwordIndex = 0;

    } else if((int)buffer[0] == 10){

      allshadows[ind] = malloc(sizeof(char) * currwordIndex);
      strcpy(allshadows[ind], currword);
      strReset(currword, currwordIndex);
      currwordIndex = 0;
      ind++;

    } else {
      currword[currwordIndex] = buffer[0];
      currwordIndex++;
    }

  }

  int i;
  for(i = 0; i < ind; i++){
    printf("%s\n", allusers[i]);
  }
  for(i = 0; i < ind; i++){
    strResize(allshadows[i]);
    //printf("\n");
    printf("%s\n", allshadows[i]);
  }

  return 0;

}
