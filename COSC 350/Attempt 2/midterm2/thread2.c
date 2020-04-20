
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void Bye(){
    printf("Bye!\n");
}

void* Thread1(){
    pthread_t id = pthread_self();
    pthread_cleanup_push(Bye, NULL);
    while(1){
        //printf("Thread 1 at cancel point\n");
        pthread_testcancel();
        sleep(1);
    }
    pthread_cleanup_pop(0);

}

void* Thread2(void *pthr){ //need to pass in pthread id for first thread (to terminate it)
    pthread_t id = (pthread_t) pthr;
    int count = 0, i;
    for(i = 0; i < 10; i++){
        count++;
        if(count == 10){
            pthread_cancel(id); //request thread cancellation
        }
    }
}

int main(){

  //Creating our threads
  pthread_t t1;
  pthread_t t2;
  
  //threads for calculating the sum/factorial
  int thr1_pt = pthread_create(&t1, NULL, Thread1, NULL);
  int thr2_pt = pthread_create(&t2, NULL, Thread2, &t1);

  if(thr1_pt != 0 || thr2_pt != 0){
      printf("Threads did not create successfully\n");
      return 0;
  }

  if(pthread_join(t1, NULL) != 0){
    printf("thread1 broke\n");
    return 0;
  }

  if(pthread_join(t2, NULL) != 0){
    printf("thread2 broke\n");
    return 0;
  }

  return 0;

}