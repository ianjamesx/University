#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
/*
void readFile(int fd) {
    char buffer[10];
    int bytes_read;
    int k = 0;
    do {
        char t = 0;
        bytes_read = read(fd, &t, 1);
        buffer[k++] = t;
        printf("%c", t);
        if(t == '\n' && t == '\0') {
            printf("%d", atoi(buffer));
            int i;
            for(i=0; i<10; i++)
                buffer[i]='\0';
            k = 0;
        }
    }
    while (bytes_read != 0);
}
*/

int main(int argc, char *argv){

  char *infile = "foo", *outfile = "clone1";
  int filedes[3];

  if (access(infile, F_OK) == 0) {
      filedes[0] = open(infile, O_RDONLY);
  } else {
      printf("Can't open in file\n");
  }

  if (access(outfile, F_OK) == 0) {
      filedes[1] = open(outfile, O_RDWR);
  } else {
    printf("Can't open out file\n");
  }

  printf("Opened files with filedes: %d, %d\n", filedes[0], filedes[1]);

  char buffer[1];
  int nread;
  while ((nread = read(filedes[0], buffer, 1) > 0)){
    printf("reading: %d, %c\n", nread, buffer[0]);
    write(filedes[1], buffer, nread);
  }

  close(filedes[0]);
  close(filedes[1]);

  return 0;

}
