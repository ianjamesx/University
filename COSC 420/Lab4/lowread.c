
void readfile(char *name){

  //read in data from shadow.txt

  umask(0);
  int sfiledes = open(name, O_RDONLY);
  //get file size
  int sfilesize = lseek(sfiledes, O_RDONLY, SEEK_END);
  //set back to begining
  lseek(sfiledes, 0, SEEK_SET);
  int lines = countLines(sfiledes);

  char **shadow;
  shadow = malloc(sfilesize * sizeof(char*));

  char buffer[1];
  int nread;
  int i = 0, start = 0, end = 0, size = 0;
  while ((nread = read(sfiledes, buffer, 1) > 0)){

    size++;

    if((int)buffer[0] == 10){
      shadow[i] = malloc(size * sizeof(char));
      storeLine(sfiledes, start, end, size, shadow, i);
      i++;
      end = start;
      size = 0;
      printf("%d\n", i);
    } else {

      end++;
      size++;

    }
    //printf("reading: %d, %c\n", nread, buffer[0]);
    //write to clone1
    //printf("%c\n", buffer[0]);
  }

}

void storeLine(int filedes, int start, int end, int size, char **contents, int index){


}

int countLines(int filedes){

  char buffer[1];
  int nread;
  int lcount = 0;
  while ((nread = read(filedes, buffer, 1) > 0)){
    if((int)buffer[0] == 10){
      lcount++;
      printf("%d\n", lcount);
    }
  }

  //reset file
  lseek(filedes, 0, SEEK_SET);

  return lcount;

}
