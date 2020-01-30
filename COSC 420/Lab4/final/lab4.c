#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <mpi.h>
#include <time.h>
#include <math.h>

/*

Hacker lab

Here's what I could find after ~3 hours on the cluster:

maria: password123
bob: fluffy
george: red32
jtanderson: 100nodes
alice: 99puppy
rmshifler: 1genius

*/

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

//first, brute force all dictionary words
//not actually needed as alphanumeric covers this
void alpha(char shadow[][100], char dict[][100], char users[][100], int shadowcount, int start, int end){
  int i, j;
  char* salt = "$1$ab";
  for(i = start; i < end; i++){
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

//try all alphanumeric combinations (eg using 1, 12 -> 99999 as prefix or suffix)
void alphanumeric(char shadow[][100], char dict[][100], char users[][100], int shadowcount, int start, int end, int max){
  int i, j, ps;
  char* salt = "$1$ab";

  /*

  perform prefixes and suffixes seperately
  as the prefix gets overwritten by suffix

  strange side effect of crypt() call
  gave false positives
  */

  for(i = start; i < end; i++){ //loop through words, this gets parallelized

    for(ps = 0; ps < max; ps++){

      //get the word appended to a prefix/suffix
      char preword[strlen(dict[i]) + numDigits(ps)];
      prefix(ps, dict[i], preword);

      //encrypt
      char* prefixCrypt = crypt(preword, salt);

      //check both to all shadow files
      for(j = 0; j < shadowcount; j++){
        if(strcmp(prefixCrypt, shadow[j]) == 0){
          printf("User %s has password %s\n", users[j], preword);
        }
      }
    }

    for(ps = 0; ps < max; ps++){

      //get the word appended to a suffix
      char sufword[strlen(dict[i]) + numDigits(ps)];
      suffix(ps, dict[i], sufword);

      //encrypt
      char *suffixCrypt = crypt(sufword, salt);

      //check both to all shadow files
      for(j = 0; j < shadowcount; j++){
        if(strcmp(suffixCrypt, shadow[j]) == 0){
          printf("User %s has password %s\n", users[j], sufword);
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

  //hardset sizes
  int dictlines = 235886, shadowlines = 11;
  int hardsize = 100; //max string size

  /*

  I attempted to:

  -read files in on master node
  -create a window to share the full dictionary with other nodes in comm world

  However, issues arose with dynamic allocation for the dictionary on master node

  as you need to dynamically allocate on master node for a window, shared memory was not an option here

  So, all nodes read in individually (not great, but somewhat fast, and works)

  */

/*
  //for splitting communication
  int nodesize, noderank;
  MPI_Comm nodecomm;
  MPI_Comm_split_type(MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, rank, MPI_INFO_NULL, &nodecomm);
  MPI_Comm_size(nodecomm, &nodesize);
  MPI_Comm_rank(nodecomm, &noderank);

  char dict[dictlines][hardsize];

  int localdictsize = 0;
  char localdict[dictlines][hardsize];

  MPI_Win windict;

  MPI_Aint winsize;
  int windisp;

  //root allocates for dictionary
  if (noderank == 0){
    localdictsize = dictlines;
  }

  if (noderank != 0){
    MPI_Win_shared_query(wintable, 0, &winsize, &windisp, &table);
  }

  MPI_Win_fence(0, wintable);
*/

//  if(rank == 0){

    int filedes[2];

    filedes[0] = open("words.txt", O_RDONLY);
    filedes[1] = open("shadow.txt", O_RDONLY);

    if(filedes[0] == -1 || filedes[1] == -1){
      printf("File open err\n");
      return 0;
    }

    char allwords[dictlines][hardsize]; // = calloc(sizeof(char*), dictbytes)
    char allshadows[shadowlines][hardsize];
    char allusers[shadowlines][hardsize];

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

    //read in/parse shadow file data
    while ((nread = read(filedes[1], buffer, 1) > 0)){

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

    int i;
    for(i = 0; i < shadowlines; i++){
      //printf("%s\n", allshadows[i]);
    }

    //splitting work load amount nodes
    int ops = ceil(dictlines / wsize);
    int low = rank * ops, high = low + ops;

    if(rank == 0){
      printf("Message from root: we have %d words, %d per node, %d nodes\n", dictlines, ops, wsize);
    }

    clock_t begin = clock();

    int max = 9999; //max digits to append (prefix/suffix)

    alpha(allshadows, allwords, allusers, shadowlines, low, high);
    alphanumeric(allshadows, allwords, allusers, shadowlines, low, high, max);

    MPI_Barrier(MPI_COMM_WORLD);

    if(rank == 0){
      clock_t end = clock();
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("Time to process: %.4f\n", time_spent);
    }

//  }

  MPI_Finalize();

  return 0;

}
