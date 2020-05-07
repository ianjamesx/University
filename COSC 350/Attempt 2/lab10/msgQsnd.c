#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>

struct msgbuffer{
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
    buf.type = 1;
    char* input = (char*) calloc(256, sizeof(int));

    printf("Enter two inerger values:\n");

    while(fgets(input, 256, stdin), !feof(stdin)){
        sscanf(input, "%d%d", &buf.one, &buf.two); //convert input to ints
        if (msgsnd(Qid, (struct msgbuffer*) &buf,  2 * sizeof(int), 0) == -1){ //send inputs to msg buffer
            perror("msgsnd() error");
        }
        printf("Enter two inerger values:\n");
    }

    // Removing the message queue
    if(msgctl(Qid, IPC_RMID, NULL) == -1){
        perror("msgctl() error.");
        exit(1);
    }

    return 0;
}