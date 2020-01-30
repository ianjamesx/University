#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
//#include <mpi.h>

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

  char *word = malloc(sizeof(char) * (preLength + sLength + sufLength));

  for(i = 0; i < preLength; i++){
    word[i] = prefix[i];
  }
  for(i = i; i < sLength; i++){
    word[i] = str[i];
  }
  for(i = i; i < sufLength; i++){
    word[i] = suffix[i];
  }

  return word;

}

//first, brute force all dictionary words
void alpha(char **shadow, char **dict, char **users, int shadowcount, int dictcount){
  int i, j;
  char* salt = "$1$ab";
  for(i = 0; i < dictcount; i++){
    for(j = 0; j < shadowcount; j++){
      char* cypertext = crypt(dict[i], salt);
      if(strcmp(cypertext, shadow[j]) == 0){
        printf("User %s has password %s\n", users[j], dict[i]);
      }
    }
  }
}

//try all alphanumeric combinations (eg using 123 as prefix or suffix)
void alphanumeric(char **shadow, char **dict, char **users, int shadowcount, int dictcount){
  int i, j, s, p;
  char* salt = "$1$ab";
  for(i = 0; i < dictcount; i++){
    for(p = 0; p < 999; p++){
      for(s = 0; s < 999; s++){
        for(j = 0; j < shadowcount; j++){
          char *word = malloc(sizeof(char) * numDigits(p) + strlen(dict[i]) + numDigits(s));
          char* cypertext = crypt(dict[i], salt);
          if(strcmp(cypertext, shadow[j]) == 0){
            printf("User %s has password %s\n", users[j], dict[i]);
          }

        }
      }
    }
  }
}

int main(int argc, char **argv){

  //hard coded file data (for dictionary and for shadow file)
  //retrieved from wc command (hacker-method)

  int dictbytes = 2493109, dictlines = 235886;
  int shadowbytes = 639, shadowlines = 10;

  //Maria passwd = password123
  //Bob passwd = fluffy
/*
  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
*/
  if(argc < 2){
    printf("Usage: ./crypt [string]\n");
    return 0;
  }

  char* salt = "$1$ab";
  char* cypertext = crypt(argv[1], salt);
  printf("Hashed Passwd: %s\n", cypertext);

  //MPI_Finalize();

  return 0;

}
