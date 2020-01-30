#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

//clearing a string
void strReset(char word[], int strsize){
  int i;
  for(i = 0; i < strsize; i++){
    word[i] = '\0';
  }
}

//for manually appending a \0 at the end of a string
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

//string to int (not used)
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
void intToString(int n, char str[]){
  sprintf(str, "%d", n);
}

void prefix(int pre, char *str, char output[]){

  int sLength = strlen(str);
  int preLength = numDigits(pre);
  int i;

  char prefix[preLength];
  intToString(pre, prefix);

  int wordsize = (preLength + sLength);

  for(i = 0; i < preLength; i++){
    output[i] = prefix[i];
  }

  int localindex = 0;
  for(i = preLength; i < (sLength + preLength); i++){
    output[i] = str[localindex];
    localindex++;
  }

  output[wordsize] = '\0'; //string may not be terminated correctly, add \0 to end

}

void suffix(int suf, char *str, char output[]){

  int sLength = strlen(str);
  int sufLength = numDigits(suf);
  int i;

  char suffix[sufLength];
  intToString(suf, suffix);

  int wordsize = (sLength + sufLength);

  for(i = 0; i < sLength; i++){
    output[i] = str[i];
  }

  int localindex = 0;
  for(i = sLength; i < wordsize; i++){
    output[i] = suffix[localindex];
    localindex++;
  }

  output[wordsize] = '\0'; //string may not be terminated correctly, add \0 to end

}

//first, brute force dictionary word
/*
void alpha(char *word, char **shadow, char **users, int shadowcount, int start, int end){
  int i, j;
  char* salt = "$1$ab";
  for(i = start; i < end; i++){
    char* cypertext = crypt(dict[i], salt);
    for(j = 0; j < shadowcount; j++){
      if(strcmp(cypertext, shadow[j]) == 0){
        printf("User %s has password %s\n", users[j], dict[i]);
      }
    }
  }
}
*/

//try all alphanumeric combinations (eg using 1, 12 -> 99999 as prefix or suffix)
void alphanumeric(char *word, char shadow[][100], char users[][100], int shadowcount, int start, int end){

  int i, j, ps;

  char* salt = "$1$ab";

  for(ps = start; ps < end; ps++){

    //get the word appended to a prefix/suffix
    char preword[strlen(word) + numDigits(ps)];
    prefix(ps, word, preword);

    //encrypt
    char* prefixCrypt = crypt(preword, salt);

    //printf("%s %s\n", preword, prefixCrypt);

    //check both to all shadow files
    for(j = 0; j < shadowcount; j++){
      if(strcmp(prefixCrypt, shadow[j]) == 0){
        printf("User %s has password %s\n", users[j], preword);
      }
    }
  }

  for(ps = start; ps < end; ps++){

    //get the word appended to a suffix
    char sufword[strlen(word) + numDigits(ps)];
    suffix(ps, word, sufword);

    //encrypt
    char *suffixCrypt = crypt(sufword, salt);

    //printf("%s %s\n", sufword, suffixCrypt);

    //check both to all shadow files
    for(j = 0; j < shadowcount; j++){
      if(strcmp(suffixCrypt, shadow[j]) == 0){
        printf("User %s has password %s\n", users[j], sufword);
      }
    }
  }
}

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //hardset sizes
  int shadowlines = 11;
  int hardsize = 100; //max string size

  int filedes;

  filedes = open("shadow.txt", O_RDONLY);

  char *word = "nodes";

/*
  if(argc < 2){
    printf("Enter a word\n");
    MPI_Finalize();
    return 0;
  }
*/

  if(filedes == -1){
    printf("File open err\n");
    MPI_Finalize();
    return 0;
  }

  char allshadows[shadowlines][hardsize];// = malloc(sizeof(char*) * shadowlines);
  char allusers[shadowlines][hardsize];// = malloc(sizeof(char*) * shadowlines);

  char buffer[1];
  char currword[hardsize];
  int nread, currwordIndex = 0, ind = 0;

  //read in/parse shadow file data
  while ((nread = read(filedes, buffer, 1) > 0)){

    if((int)buffer[0] == 58){ //:

      strcpy(allusers[ind], currword);
      strReset(currword, currwordIndex);
      currwordIndex = 0;

    } else if((int)buffer[0] == 10){

      strcpy(allshadows[ind], currword);
      strReset(currword, currwordIndex);
      currwordIndex = 0;
      ind++;

    } else {
      currword[currwordIndex] = buffer[0];
      currwordIndex++;
    }

  }

  //splitting work load amount nodes

  clock_t begin = clock();

  int max = 999;

  int ops = max / wsize;
  int low = rank * ops, high = low + ops;

  if(rank == 0){
    printf("Message from root: we have word %s, appending 0 --> %d on prefix/suffix\n", word, max);
  }

  //printf("Rank %d checking in: %d --> %d\n", rank, low, high);

  alphanumeric(word, allshadows, allusers, shadowlines, low, high);

  close(filedes);

  if(rank == 0){
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time to process: %.4f\n", time_spent);
  }

  MPI_Finalize();

  return 0;

}
