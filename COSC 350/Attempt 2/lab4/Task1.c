#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


int stringtoint(char*);
int isdig(char);
void closefiles(int[], int);
int convIntToStr(char*, int);

int main(int argc, char **argv){

  if(argc < 2){
    printf("Usage: ./task1 [inputfile]\n");
    return 0;
  }

  char *infile = argv[1];
  int filedes = open(infile, O_RDONLY);

  //buffers for temporary read in, and full number
  char temp;
  char buffer[80];
  int curr = 0;

  //read input, check if curr char is digit
  while(read(filedes, &temp, 1) > 0){
    if(isdig(temp)){
      buffer[curr] = temp;
      curr++;
    }
  }

  buffer[curr] = '\0'; //end string

  int numb = stringtoint(buffer);
  numb += 10;

  char intstr[80]; //buffer for string conversion
  int strsize = convIntToStr(intstr, numb);

  write(1, intstr, strsize); //write out

  close(filedes);

  return 0;

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

int stringtoint(char *c){
  int i = 0, num = 0;
  while(c[i] != '\0'){
    num = 10 * num + (c[i] - '0');
    i++;
  }
  return num;
}

void closefiles(int filedes[], int fdcount){
  int i;
  for(i = 0; i < fdcount; i++){
    close(filedes[i]);
  }
}

int convIntToStr(char *str, int x){
  sprintf(str, "%d", x);
  return strlen(str);
}
