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

int main(int argc, char **argv){

  int filedes[1];

  filedes[0] = open("words.txt", O_RDONLY);
  printf("%d\n", filedes[0]);
  if(filedes[0] == -1){
    printf("Not happening...\n");
    return 0;
  }

  int dictbytes = 2493109, dictlines = 235886;
  int shadowbytes = 639, shadowlines = 10;

  int wordcount = dictlines;
  int hardsize = 100;

  char allwords[dictlines][hardsize];// = calloc(sizeof(char*), dictbytes);

  //create buffer to hold one char (one byte)
  char buffer[1];
  char currword[hardsize];
  int nread, currwordIndex = 0, ind = 0;
  while ((nread = read(filedes[0], buffer, 1) > 0)){
    if((int)buffer[0] == 10){
      //allwords[ind] = calloc(sizeof(char), currwordIndex);
      strcpy(allwords[ind], currword);
      strReset(currword, currwordIndex);
      currwordIndex = 0;
      ind++;
    } else {
      currword[currwordIndex] = buffer[0];
      currwordIndex++;
    }

    //printf("%s\n", allwords[ind]);
  }

  int i;
  for(i = 0; i < ind; i++){
    printf("%s\n", allwords[i]);
  }
/*
  for(i = 0; i < strlen(allwords[ind-1]); i++){
    printf("%c ", allwords[ind-1][i]);
  }
*/
  return 0;

}
