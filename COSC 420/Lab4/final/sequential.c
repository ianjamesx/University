#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <mpi.h>

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

int stringtoint(char *c){

  //convert string to int
  //cant use atoi

  int i = 0, num = 0;
  while(c[i] != '\0'){
    num = 10 * num + (c[i] - '0');
    i++;
  }

  return num;

}

int numDigits(int n){

  int count = 0;

  while(n != 0){
    count++;
    n /= 10;
  }

  return count;

}

//too slow
//fix this
void intToString(int n, char *str){
  sprintf(str, "%d", n);
}

char* appendPreSuf(int pre, int suf, char *str){

  int sLength = strlen(str);
  int preLength = numDigits(pre), sufLength = numDigits(suf);
  int i, j = 0;

  char *prefix = malloc(sizeof(char) * preLength), *suffix = malloc(sizeof(char) * sufLength);
  intToString(pre, prefix);
  intToString(suf, suffix);

  int wordsize = (preLength + sLength + sufLength);

  char *word = malloc(sizeof(char) * wordsize);

  for(i = 0; i < preLength; i++){
    word[i] = prefix[i];
  }

  int localindex = 0;
  for(i = preLength; i < (sLength + preLength); i++){
    word[i] = str[localindex];
    localindex++;
  }

  localindex = 0;
  for(i = (sLength + preLength); i < wordsize; i++){
    word[i] = suffix[localindex];
    localindex++;
  }

  word[wordsize] = '\0'; //string may not be terminated correctly, add \0 to end
  return word;

}

//first, brute force all dictionary words
void alpha(char **shadow, char dict[][100], char **users, int shadowcount, int dictcount){
  int i, j;
  char* salt = "$1$ab";
  for(i = 0; i < dictcount; i++){
    char* cypertext = crypt(dict[i], salt);
    for(j = 0; j < shadowcount; j++){
      if(strcmp(cypertext, shadow[j]) == 0){
        printf("User %s has password %s\n", users[j], dict[i]);
      }
    }

    if(i % 1000 == 0){
    //  printf("%d / %d words tested\n", i, dictcount);
    }
  }
}

//try all alphanumeric combinations (eg using 123 as prefix or suffix)
void alphanumeric(char **shadow, char dict[][100], char **users, int shadowcount, int dictcount){
  int i, j, s, p;
  char* salt = "$1$ab";

  for(i = 0; i < dictcount; i++){
    for(p = 0; p < 999; p++){
      for(s = 0; s < 999; s++){
        char *word = malloc(sizeof(char) * (numDigits(p) + strlen(dict[i]) + numDigits(s)));
        word = appendPreSuf(p, s, dict[i]);
        char* cypertext = crypt(word, salt);
        //printf("%s\n", word);

        for(j = 0; j < shadowcount; j++){
          if(strcmp(cypertext, shadow[j]) == 0){
            printf("User %s has password %s\n", users[j], dict[i]);
          }
        }

      }
    }
  }
}

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0){

    int filedes[2];

    filedes[0] = open("words.txt", O_RDONLY);
    if(filedes[0] == -1){
      return 0;
    }

    filedes[1] = open("shadow.txt", O_RDONLY);
    if(filedes[0] == -1){
      return 0;
    }

    int dictlines = 235886, shadowlines = 11;
    int hardsize = 100;

    char allwords[dictlines][hardsize]; // = calloc(sizeof(char*), dictbytes)
    char **allshadows = malloc(sizeof(char*) * shadowlines);
    char **allusers = malloc(sizeof(char*) * shadowlines);

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
    }

    //reset reader data
    strReset(currword, currwordIndex);
    currwordIndex = 0;
    ind = 0;

    while ((nread = read(filedes[1], buffer, 1) > 0)){

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

    //sometimes the hash gets two characters appended to the back
    //take those off
    int i;
    for(i = 0; i < shadowlines; i++){
      strResize(allshadows[i]);
    }

    //alpha(allshadows, allwords, allusers, shadowlines, dictlines);
    alphanumeric(allshadows, allwords, allusers, shadowlines, dictlines);

  }

  MPI_Finalize();

  return 0;

}
