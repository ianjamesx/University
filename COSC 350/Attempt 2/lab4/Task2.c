#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

int stringtoint(char*);
void writeasciichar(int, char[]);

int main(int argc, char **argv){

  if(argc < 3){
    printf("Usage: ./task2 [asciifile] [outputfile]\n");
    return 0;
  }

  char *infile = argv[1], *outfile = argv[2];
  int filedes[2];
  filedes[0] = open(infile, O_RDONLY);
  filedes[1] = open(outfile, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP);

  char b[1], currchar[4]; //most we'll need is three characters, ascii only goes to 256 (one extra for the \0)
  int curr = 0;

  //read input, check if curr char is digit
  while(read(filedes[0], b, 1) > 0){
    if(b[0] == ' '){
      currchar[curr] = '\0'; //end string
      writeasciichar(filedes[1], currchar); //write to follow
      curr = 0; //reset curr
      printf("%s\n", currchar);
    } else {
      currchar[curr] = b[0];
      curr++;
    }
  }

  return 0;

}

int stringtoint(char *c){

  //convert string to int

  int i = 0, num = 0;
  while(c[i] != '\0'){
    num = 10 * num + (c[i] - '0');
    i++;
  }

  return num;

}

void writeasciichar(int fd, char ascii[]){

  int asciival = stringtoint(ascii);
  char test = asciival; //coerce to char
  write(fd, &test, 1); //write to output file

}
