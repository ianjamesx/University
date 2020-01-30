//write.c
#include <unistd.h>
#include <stdlib.h>
int main(){

 if ((write (1, "Here is some data\n", 18)) != 18){
  write (2, "error on file descriptor 1\n", 46);
 }

  exit(0);
}
