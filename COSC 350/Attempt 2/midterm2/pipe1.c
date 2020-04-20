//open pipe from parent --> child
//parent takes two int input, child multiplies
//continue until EOF sent to child

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//better to declare ends of the pipe than to try to remember 0 or 1 (my memory is fucked)
int READ_END=0;
int WRITE_END=1;

int main(){

  //since we are sending data parent --> child
  //then later child --> parent (to print)
  //we need two pipes
  //not all linux systems support bi-directional pipes
  
  //pipe1 - for parent sending input to child
  //pipe2 - for child sending output to parent
  int pipe1[2], pipe2[2]; 

  if(pipe(pipe1) < 0){
    printf("Could not open pipe1\n");
    return 0;
  }

  if(pipe(pipe2) < 0){
    printf("Could not open pipe2\n");
    return 0;
  }
  
  pid_t pid = fork();
  
  if(pid == 0){ //child process
    
    //Close the input pipe1/output pipe2 from the child's side.
    close(pipe1[WRITE_END]);
    close(pipe2[READ_END]);
    int a, b;
    char buf[256];
    bool running=true;
    
    while(read(pipe1[READ_END], buf, 256) > 0){
      //printf("child recieved: %s\n", buf);
      //Convert to integers 
      if(sscanf(buf, "%d %d", &a,&b)!=2){
        printf("data passed to child wasn't two integers");
        return 0;
      }

        printf("child calculating: %d * %d\n", a,b);
        int result = a * b;
        char res[256];
        sprintf(res, "%d", result); //convert result to string (to send over pipe)
        write(pipe2[WRITE_END], res, sizeof(res)); //send output back to parent through pipe

    }
    
    printf("child recv'd EOF and closed pipe\n");
    close(pipe1[READ_END]); //close pipes
    close(pipe2[WRITE_END]);
    
  } else if(pid > 0){ //parent process
    
    //Close the input pipe from the parent's side/output of second pipe
    close(pipe1[READ_END]);
    close(pipe2[WRITE_END]);
    printf("Input two ints \npress enter to pipe to the child\n");
    
    int a, b;
    bool running = true;
    char buf[256];
    
    while(running){
      memset(buf, '\0', 256); //Need to set the string to null or else we'll get weird loops on single integer inputs. 
      read(0, buf, 256); 
      if(sscanf(buf,"%d %d", &a, &b) != 2){ //incorrect input (user wants to exit)
        
        close(pipe1[READ_END]); //trigger EOF in child
        close(pipe2[WRITE_END]);
        running = false;
        
      } else { //input is correct
        printf("Parent sending inputs to the child...\n");
        write(pipe1[WRITE_END], buf, sizeof(buf)); //send to child
      }

      while(read(pipe2[READ_END], buf, 256) > 0){ //get output from child
        printf("Result: %s\n", buf);
        break; //need this break or else this loop will block parent
      }
      
    }
    
  }
  
}
