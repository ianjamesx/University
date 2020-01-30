#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <mpi.h>

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

void alpha(char **shadow, char **dict, int shadowcount, int dictcount){

  int i, j;
  char* salt = "$5$ab";
  for(i = 0; i < dictcount; i++){
    for(j = 0; j < shadowcount; j++){
      char* cypertext = crypt(dict[i], salt);
      if(strcmp(cypertext, shadow[j]) == 0){
        printf("Matched: %s -> %s\n", dict[i], cypertext);
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

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(argc < 2){
    printf("Usage: ./crypt [string]\n");
    return 0;
  }

  char* salt = "$5$ab";
  char* cypertext = crypt(argv[1], salt);
  printf("Hashed Passwd: %s\n", cypertext);

  MPI_Finalize();

  return 0;

}
