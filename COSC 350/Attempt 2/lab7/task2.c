/* Catch ^C with sigaction
 * A. Copy ctrlc1.c from BLP4th edition page 483, 466 in 3rd edition. Run it to see how it behaves.
 * B. Copy ctrlc2.c from BLP4th edition page 488, 470 in 3rd edition. Run it to see how it behaves. Not that it does not behave exactly like ctrlc1.
 * C. BLP advises using SIGQUIT (^\) to quit from ctrlc2. Try it to see how it behaves.
 * D. As an alternative way to quit from it, put it in the background, then issue a kill. Write down a brief description of exactly what you did.
 * E. Modify your ctrlc2.c so it behaves exactly the same as ctrl1.c Hint: read the sigaction Flags section of BLP, Chapter 11.
 * F. Print your modified ctrlc2.c to hand in.
 * G. While we're at it, take a look at what is printed by kill -l. It's an easy way to get a list of all the signal numbers and names.
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig){
  printf("\nOUCH - I got a signal %d\n", sig);
}

int main(){
  struct sigaction act;

  act.sa_handler = ouch;
  sigemptyset(&act.sa_mask);
  act.sa_flags=SA_RESETHAND;

  sigaction(SIGINT, &act,0);

  while(1){
    printf("Hello world!\n");
    sleep(1);
  }
  
  return 0;
}
