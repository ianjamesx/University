
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct user {
    char *fname, *lname, *id;
};

int stringtoint(char *c){

  //convert string to int
  int i = 0;
  long int num = 0;
  while(c[i] != '\0'){
    num = 10 * num + (c[i] - '0');
    i++;
  }

  return num;

}

int main(int argc, char **argv){

    if(argc < 2){
        printf("Usage: ./program [number of structures]");
        return 0;
    }

    int n = stringtoint(argv[1]);
    int i;

    struct user *u;
    u = (struct user*) malloc(n*sizeof(struct user)); //allocate n structures

    for(i = 0; i < n; i++){

        char b[50]; //just a buffer

        //scan first name
        printf("Enter First Name for user %d: ", i);
        scanf("%s", b);
        size_t flen = strlen(b);
        u[i].fname = malloc(flen+1);
        strcpy(u[i].fname, b);

        //scan last name
        printf("Enter Last Name for user %d: ", i);
        scanf("%s", b);
        size_t llen = strlen(b);
        u[i].lname = malloc(llen+1);
        strcpy(u[i].lname, b);

        //scan id
        printf("Enter ID for user %d: ", i);
        scanf("%s", b);
        size_t idl = strlen(b);
        u[i].id = malloc(idl+1);
        strcpy(u[i].id, b);

    }

    printf("\n");

    for(i = 0; i < n; i++){
        printf("User %d: %s %s %s\n", i, u[i].fname, u[i].lname, u[i].id);
    }

    return 0;

}