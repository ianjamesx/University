
/* sigprocmask
* Write a complete C program that demonstrates how you can block and unblock signals. Your program will have two loops, each of which will simply print the integers from 1 to 5 at 1 second intervals. During the first loop, SIGINT and SIGQUIT are blocked. During the second loop, only SIGINT is blocked.
* While the program is running, you can try ^C and/or ^\ to see if they are blocked as expected.
* The signal SIGINT is usually bound to ^C by the terminal driver. The SIGINT signal terminates the program by default.
* The signal SIGQUIT is usually bound to ^\ by the terminal driver. The signal SIGQUIT by default causes the program to terminate and creates a core file.
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int handler(int sig){
 if(sig==SIGQUIT)
   printf("SIGQUIT pressed during the loop\n");
 else if(sig==SIGINT)
   printf("SIGINT pressed during the loop\n");
}

int main(){

 sigset_t new_set, old_set;
 sigemptyset(&new_set); //Clear all signals
 // Add the two signals to the signal set
 sigaddset(&new_set, SIGINT);
 sigaddset(&new_set, SIGQUIT);
 //Overwrite the signal set.
 sigprocmask(SIG_BLOCK, &new_set, &old_set);

 int i=0;
 /* First loop where SIGINT and SIGQUIT are blocked */
 for(i=0; i<5; i++){
   printf("First loop(SIGINT & SIGQUIT blocked): %d\n", i);
   sleep(1);
 }

 printf("Unblocking SIGQUIT\n");
 //Now, let's redirect the handler to a custom handler for the unblock operation, since if we don't it'll exit.
 signal(SIGINT, handler);
 signal(SIGQUIT, handler);
 //Reset to default mask
 sigprocmask(SIG_SETMASK, &old_set, NULL);
 //Edit our mask to only include SIGINT
 sigdelset(&new_set, SIGQUIT);
 sigprocmask(SIG_BLOCK, &new_set, NULL);
 //Reset the handlers to default
 signal(SIGINT, SIG_DFL);
 signal(SIGQUIT, SIG_DFL);
 /* Second loop where only SIGINT is blocked */
 for(i=0; i<5; i++){
   printf("Second loop(SIGINT blocked): %d\n", i);
   sleep(1);
 }
}
