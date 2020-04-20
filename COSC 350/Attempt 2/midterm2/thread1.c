//constantly increase/decrease counter by 1
//use mutex for critical section

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int counter = 0; //counter

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER; //mutex (for race condition)

void* increase(){
    while(1){
        if(counter < 10){
            pthread_mutex_lock(&count_mutex); //lock the critical section
            counter++;
            printf("counter is now %d\n", counter);
            sleep(1);
            pthread_mutex_unlock(&count_mutex); //unlock
        }
    }
}

void* decrease(){
    while(1){
        if(counter > 0){
            pthread_mutex_lock(&count_mutex);
            counter--;
            printf("counter is now %d\n", counter);
            sleep(1);
            pthread_mutex_unlock(&count_mutex);
        }
    }
}

int main(){


  //Creating our threads
  pthread_t inc_t;
  pthread_t dec_t;
  
  //threads for calculating the sum/factorial
  int inc_pt = pthread_create(&inc_t, NULL, increase, NULL);
  int dec_pt = pthread_create(&dec_t, NULL, decrease, NULL);

  if(inc_pt != 0 || dec_pt != 0){
      printf("Threads did not create successfully\n");
      return 0;
  }

  if(pthread_join(inc_t, NULL) != 0){ //join to suspend this thread until increase terminate (which is never)
    printf("Increase thread broke\n");
    return 0;
  }

  if(pthread_join(dec_t, NULL) != 0){ //same for decrease thread
    printf("Decrease thread broke\n");
    return 0;
  }


  return 0;
}
