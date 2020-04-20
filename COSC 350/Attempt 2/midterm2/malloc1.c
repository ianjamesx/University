#include <stdlib.h>
#include <stdio.h>

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
        printf("Usage: ./program [n]");
        return 0;
    }

    //create string with malloc
    //as variable arrays do not work with some c compilers

    int n = stringtoint(argv[1]); //convert input to int
    char *str = malloc((sizeof(char)*n)+1); //allocate room for str (+1 for null terminator)

    int i;
    for(i = 0; i < n; i++){
        str[i] = rand() % 26 + 'a';
    }
    str[i] = '\0'; //null terminator

    printf("Ouput string: %s\n", str);
    free(str);

    return 0;

}