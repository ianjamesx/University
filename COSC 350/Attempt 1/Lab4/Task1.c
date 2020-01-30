
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int stringtoint(char *c){

  //convert string to int
  //cant use atoi

  int i = 0;
  long int num = 0;
  while(c[i] != '\0'){
    num = 10 * num + (c[i] - '0');
    i++;
  }

  return num;

}

int isdig(char c){

  //need to create lower and upper ranges for integer ascii
  int low = (int)'0', high = (int)'9';

  int x = (int)c;
  if(x >= low && x <= high){
    return x;
  }

  return 0;

}

int int_to_str(char str[], int x){

  sprintf(str, "%d", x);
  return (strlen(str));

}

int main(int argc, char **argv){

  if(argc < 2){
    printf("Not enough arguments, please input a filename to search, exiting\n");
    return 0;
  }

  int filedes;
  char *infile = argv[1];

  filedes = open(argv[1], O_RDONLY);
  if(filedes == -1){
    printf("Can't open input file\n");
    return 0;
  }

  //create buffer to hold one char (one byte)
  char buffer[1];
  char fullbuff[80];
  int nread;
  int i = 0;

  //printf("%d %d\n", low, high);

  while ((nread = read(filedes, buffer, 1) > 0)){

    //lets put in some special cases to skip any ascii code that isnt a number

    if(isdig(buffer[0])){

      //printf("Found int %c\n", buffer[0]);

      fullbuff[i] = buffer[0];
      //printf("Reading int %c\n", buffer[0]);
      i++;

    }

  }

  printf("Number found: %s\n", fullbuff);

  long int outint = stringtoint(fullbuff);

  outint += 10;

  char intstr[i];

  int_to_str(intstr, outint);

  printf("Number found +10: %s\n", intstr);

  close(filedes);

  return 0;

}
