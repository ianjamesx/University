#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int fd[2];

void readFile(int fd) {
    char buffer[10];
    int bytes_read;
    int k = 0;
    do {
        char t = 0;
        bytes_read = read(fd, &t, 1);
        buffer[k++] = t;
        printf("%c", t);
        if(t == '\n' && t == '\0') {
            printf("%d", atoi(buffer));
            int i;
            for(i=0; i<10; i++)
                buffer[i]='\0';
            k = 0;
        }
    }
    while (bytes_read != 0);
}

int tab[50];

int main(int argc, char *argv[]) {
    if(argv[1] == NULL || argv[2] == NULL)   {
            printf("Function requires two arguments\n");
            return -1;
    }
    else {
        if (access(argv[1], F_OK) == 0) {
            fd[0] = open(argv[1], O_RDONLY);
        }
        else {
            fd[0] = open(argv[1], O_WRONLY|O_CREAT|O_SYNC, 0700);
            const int size = 50;
            int i;
                for(i=0; i<size; i++) {
                    char buf[10];
                    sprintf(buf, "%d\n", i+1);
                    write(fd[0], buf, strlen(buf));
                }
                close(fd[0]);
            fd[0] = open(argv[1], O_RDONLY);
            if (access(argv[2], F_OK) == 0)
                fd[1] = open(argv[2], O_WRONLY);
            else
                fd[1] = open(argv[2], O_WRONLY|O_CREAT, 0700);
        }
    }

    if (access(argv[2], F_OK) == 0)
        fd[1] = open(argv[2], O_WRONLY);
    else
        fd[1] = open(argv[2], O_WRONLY|O_CREAT, 0700);

    printf("%d, %d\n", fd[0], fd[1]);

    readFile(fd[0]);
    close(fd[0]);
    close(fd[1]);
}
