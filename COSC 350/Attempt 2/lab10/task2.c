/*
consumer-producer simulation, using global count variables rather than semaphores

as we cannot use semaphores, consumer will simply wait until produces generates more, rather than
to await message from producer

vice-versa for producer when awaiting consumer's consumption of data
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>

int buffer[10]; //buffer will act as list producer puts data into, consumer removes from
int curr = 0;

void* producer(){
    while(1){
        int item = rand() % 10; //generate some random data
    	if(curr < 10){
            //theoretically, you'd put alert to consumer here if curr == 0
    		buffer[curr] = item; //put some random data into our buffer
            curr++; //we now have a new index
        } else {
    		printf("Producer cannot produce\n");
        }

        printf("Producing %d\n", item);
        
        int i;
        for(i = 0; i < 10; i++){
            printf("%d ", buffer[i]); //print our new list
        }
        printf("\n");
        sleep(1);
    }
}

void* consumer(){
    while(1){
        int temp = buffer[curr - 1]; //get last thing the producer put into our list
    	if(curr >= 0){
            //theoretically, you'd put alert to producer here if curr == 10
    		curr--;
    		buffer[curr] = -1;
    	} else {
    		printf("Consumer cannot consume\n");
        }

        printf("Consuming %d\n", temp);

        int i;
    	for(i = 0; i < 10; i++){
    		printf("%d ", buffer[i]);
        }

    	puts("");
    	sleep(2); //put delay on consumers sleep, as it will get stuck constantly consuming/producing if at same sleep as producer
    }
}

int main(int argc, char* argv[]){

    int i;
    for(i = 0; i < 10; i++){
        buffer[i] = -1; //-1 is our null value, symbolises absense of data
    }

    //threads for producer-consumer
    pthread_t threads[2];
    pthread_create(&threads[0], NULL, producer, NULL);
    pthread_create(&threads[1], NULL, consumer, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}