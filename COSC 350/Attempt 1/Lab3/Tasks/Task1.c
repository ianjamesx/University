#include <stdio.h>
#include <unistd.h>
int main(){

  char b[1];
  int nread;
  while ((nread = read(0, b, 1) > 0)){
    write (1, b, nread);
  }

  return 0;

}
