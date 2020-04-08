/* Process communication without sending signal.
 * Write a complete C program in which a child process writes a message "Hi, Mom" to a file named foo.
 * The parent process reads the message and prints it to standard output "My son said Hi Mom". The part of the message "Hi Mom" is retrieved from the file foo. Assume that all system calls succeed (no need to error check). Use only low-level file operations(fork, wait, open, close, read, write, lseek). You must make sure a child process terminates first
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(){

  umask(0);
  int fd1 = open("foo", O_CREAT | O_RDWR, 0666);
  int fd2 = dup(fd1);
  pid_t pid = fork();

  if(pid == 0){
    write(fd2, "Hi, Mom", 7);
    close(fd2);
    return 0;
  }

  wait(NULL);
  lseek(fd1, SEEK_SET,0);
  char rbuf[7]; //We are making our buffer 7 since we know exactly how much we're writing.
  read(fd1, rbuf, 7);
  printf("My son said %s\n", rbuf);
  close(fd1);

  return 0;

}
