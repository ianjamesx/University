#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

void closefiles(int[], int);
void int_to_str(int, char *, int);

int main(int argc, char **argv){

  if(argc < 3){
    printf("Not enough parameters, exiting\n");
    return 0;
  }

  char *infile = argv[1], *outfile = argv[2];
  int filedes[2];

  filedes[0] = open(infile, O_RDONLY);
  if(filedes[0] == -1){
    printf("Can't open input file, exiting\n");
    return 0;
  }

  umask(0);
  filedes[1] = open(outfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH, S_IWOTH);

  char buffer[1];
  int ascii;
  int nread;
  while ((nread = read(filedes[0], buffer, 1) > 0)){

    //do not use lib function to get ascii code
    ascii = (int)buffer[0];

    //printf("reading: %s, %d\n", buffer, ascii);

    char *asciistr; //max ascii code is 128, we only need 3 chars
    //however with two digit ascii codes, we may recieve a zero in front of our code
    //instead, determine if we need two or three characters

    if(ascii > 100){
      asciistr = malloc(3);
      int_to_str(ascii, asciistr, 3);
    } else {
      asciistr = malloc(2);
      int_to_str(ascii, asciistr, 2);
    }

    write(filedes[1], asciistr, sizeof(asciistr)); //put ascii code
    write(filedes[1], " ", 1); //then put a space between each ascii code
  }

  closefiles(filedes, 2);

  return 0;
}

void int_to_str(int ascii, char *asciibuffer, int s){

  int i;
  int asciizero = 48;
  for(i = (s-1); i >= 0; i--){
    asciibuffer[i] = ascii % 10 + asciizero;
    ascii /= 10;
  }

}


void closefiles(int filedes[], int fsize){
  int i;
  for(i = 0; i < fsize; i++){
    close(filedes[i]);
  }
}
