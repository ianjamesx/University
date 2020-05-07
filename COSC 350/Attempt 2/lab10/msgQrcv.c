#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>

struct msgbuffer {
    long type;
    int one;
    int two;
};

int main(int argc, char* argv[]){
    
    key_t key;
    if((key = ftok("msgQsnd.c", 'B')) == -1){
        perror("ftok() error.");
        exit(1);
    }

    int Qid;
    if((Qid = msgget(key, 0644 | IPC_CREAT)) == -1){ //0644 sets priviledges rw-r--r--
        perror("msgget() error.");
        exit(1);
    }

    struct msgbuffer buf;
    while(1){
        // Reads the message from buffer
        if(msgrcv(Qid, (struct msgbuffer*) &buf, 2 * sizeof(int), 0, 0) == -1){
            perror("msgrcv() error");
            exit(1);
        }
        printf("The sum of the digits recieved from 'msgQsnd.c' is %d \n", buf.one + buf.two);
    }

    return 0;
}