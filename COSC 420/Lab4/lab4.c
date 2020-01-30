#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <mpi.h>

//520 conf
//359.20 htl
//512.50 flht

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

void incStr(char *str){

}

void incrementStr(char str[]){

  char digits[] = "0123456789";

  if(str[strlen(str) - 1] == '9'){
    str[strlen(str) - 1] = 0;
  } else {

  }

}

int getNewStrSize(char *presuf, char *str){
  return (strlen(presuf) + strlen(str));
}

char* prefix(char *pre, char *str){

  int sLength = strlen(str), pLength = strlen(pre);
  int i, j = 0;

  char *newStr = malloc(sizeof(char) *(sLength + pLength));

  for(i = 0; i < pLength; i++){
    newStr[i] = pre[i];
  }

  for(i = (pLength - 1); i < sLength; i++){
    newStr[i] = str[j];
    j++;
  }

}

void suffix(char *suf, char *str){

  int sLength = strlen(str), pLength = strlen(suf);
  int i;

  for(i = 0; i < pLength; i++){
    printf("%c", suf[i]);
  }

  for(i = 0; i < sLength; i++){
    printf("%c", str[i]);
  }

}

void numeric(char *hash, char *salt){
  char *prefix, *suffix;
  int i;
  //strcpy(str, "these ");
}

int main(int argc, char **argv){

  //hard coded file data (for dictionary and for shadow file)
  //retrieved from wc command (hacker-method)

  int dictbytes = 2493109, dictlines = 235886;
  int shadowbytes = 639, shadowlines = 10;

  //Maria passwd = password123
  //Bob passwd = fluffy

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(argc < 2){
    printf("Usage: ./crypt [string]\n");
    return 0;
  }

  //char str[];
  //char *new = malloc(sizeof(char) * getNewStrSize("Hello", "test"));
  //new = prefix("HEllo", "test");
  //printf("%s\n", new);

  char* salt = "$1$ab";
  char* cypertext = crypt(argv[1], salt);
  printf("Hashed Passwd: %s\n", cypertext);

  MPI_Finalize();

  return 0;

}
