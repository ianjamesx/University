#include <stdio.h>
#include <fcntl.h>
struct Citenode {
  int index;
  struct Citenode *next;
};

void printcitelink(int origin, struct Citenode *cl){
  struct Citenode *curr = cl;
  printf("%d -> ", origin);
  while(curr != NULL){
    printf("%d ", curr->index);
    curr = curr->next;
  }
  printf("\n");
}


//from an array of citations (paper IDs)
//build a linked list of paper indices
void buildCiteList(struct DITree* dt, char *origin, char **citations, int nc, struct Citenode* citearray[]){

  int originIndex = DITree_get_index(dt, origin);
  if(originIndex == -1) {
    //printf("%s not found in tree\n", origin);
    return;
  }
  struct Citenode *start = (struct Citenode*)malloc(sizeof (struct Citenode));
  start->next = NULL;
  struct Citenode *curr = start;

  int i;

  //nc=number of citations (how many char*s in citations)
  for(i = 1; i < nc; i++){

    int currindex = DITree_get_index(dt, citations[i]);
    if(currindex == -1) {
      continue;

    }
    curr->next = (struct Citenode*)malloc(sizeof (struct Citenode)); //make a new one after it
    curr = curr->next;
    curr->index = currindex;
  }

  //printcitelink(originIndex, start);

  //dont store the origin index in the list
  //we cant get that throught the index of the array
  //instead, store the starting cite node
  citearray[originIndex] = start->next;

  //printf("\n\n");

  free(start); //dont need start anymore, that was just a temp incase we didnt have a linked list lol

}

void buildCSRfromCitearr(struct CSRgraph *csr, struct Citenode *citearray[], int papercount){

  //lets just make some buffers now
  //we'll resize later for efficiency
  //or we might not (budget cuts)

  int buffersize = 15000000;
  int offsets[buffersize];
  int sources[buffersize];

  offsets[0] = 0; //init first offset
  int currsource = 0;

  int i;
  for(i = 0; i < papercount; i++){

    //iterate through list for each citation list
    struct Citenode *curr = citearray[i];
    while(curr != NULL){

      //set current source to be index of citation
      sources[currsource] = curr->index;
      currsource++;

      //move to next, delete old
      struct Citenode *temp = curr;
      curr = curr->next;
      free(temp);

    }

    offsets[i+1] = currsource;
  }

  //finally, set the graph with all our temp data
  setgraph(csr, offsets, sources, papercount, currsource);

}

void capstring(char str[], int size){
  str[size] = '\0';
}

int readline(char str[], int fd){
  char buffer[1];
  int nread, curr = 0;
  while ((nread = read(fd, buffer, 1) > 0)){
    if(buffer[0] == '\n'){
      capstring(str, curr);
      return curr;
    }
    str[curr] = buffer[0];
    curr++;
  }
  return -1;
}

void printcitelist(char *list[], int numcites){
  int i;
  for(i = 0; i < numcites; i++){

    if(i == 0){
       printf("origin: %s\n", list[i]);
       continue;
     }

    printf("%s\n", list[i]);
  }
  printf("\n~~~\n");
}


//TESTING//////////////////////////

/*
void arbitraryInsert(struct DITree *dt, char *id, int index){

  if(DITree_get_index(dt, id) == -1){

    DocIndex* di;
    create_DocIndex(&di, id, index);
    DITree_insert_di(dt, di);

  }

}
*/

int paperdelim(char *line){
  if(strcmp(line, "+++++") == 0){
    return 1;
  }
  return 0;
}

int citedelim(char *line){
  if(strcmp(line, "-----") == 0){
    return 1;
  }
  return 0;
}

/*
void setArbitraryIndices(char **allcontent, int numcites, struct DITree* dt){

  int i;

  int curr = 0;
  for(i = 0; i < numcites; i++){

    //skip delims
    if(paperdelim(allcontent[i])) continue;
    if(citedelim(allcontent[i])) continue;

    arbitraryInsert(dt, allcontent[i], curr);
    curr++;

    if(i % 200000 == 0) printf("(arbitrarily) set index %d...\n", i);

  }

}
*/
////////////////////////////

//convert linked list of cites to an array of cite strings
//NOTE: this is invidividual for each paper
//ran after each individual linked list is created
void formatCites(char *cites[], int numcites, struct Citenode *citationlist[], struct DITree* dt){

  int i;

  //copy origin paper
  char *origin = malloc(sizeof(char*) * strlen(cites[0]));
  strcpy(origin, cites[0]);

  //put this list in citationlist
  buildCiteList(dt, origin, cites, numcites, citationlist);

}

//put cites into individual cite arrays
//numcites is count of all citations in file
int processCites(char *allcontent[], long int numcites, struct DITree* dt, struct Citenode *citationlist[]){

  int i;
  int currcitecount = 0;
  int maxcitesperpaper = 6000; //theres one paper (around index 21000) with a fuckton of citations
  int allcites = 0;

  char *curr[maxcitesperpaper];

  for(i = 0; i < numcites; i++){

    //when we hit a ++++++
    //get the linked list into the array
    //reset it (we have to reallocate cause formatCites deletes it after its read)
    if(paperdelim(allcontent[i])){
      formatCites(curr, currcitecount, citationlist, dt);
      currcitecount = 0;
      continue;
    }

    if(citedelim(allcontent[i])){
      continue; //just skip the ------ lines
    }

    //copy from full list to array
    curr[currcitecount] = (char *)malloc(sizeof(char) * strlen(allcontent[i]));
    strcpy(curr[currcitecount], allcontent[i]);
    currcitecount++;
    allcites++;

    //free malloc'd strings whle we're at it

  //  if(i % 200000 == 0) printf("processed citation %d...\n", i);

  }

//  printf("finished processing cites...\n");

  //the last one will never get hit since there is no +++++ to end file
  //just do it manually here

  formatCites(curr, currcitecount, citationlist, dt);

  //lets also free everything in our curr buffer
  //(do this later)

//  printf("lines: %d citations: %d\n", numcites, allcites);
  return allcites;

}

void initcitelist(struct Citenode *citationlist[], int size){
  int i;
  for(i = 0; i < size; i++){
    citationlist[i] = NULL;
  }
}

void debugprintCitelist(struct Citenode *citationlist[], int size){

  int i;
  for(i = 0; i < size; i++){
    struct Citenode *curr = citationlist[i];
    printf("%d -> ", i); //current index is paper
    while(curr != NULL){
      printf("%d, ", curr->index);
      curr=curr->next;
    }
    printf("\n"); //end current list
  }

}

int readfile(char *filename, struct DITree* dt, struct Citenode *citationlist[], int linecount){
  int fd = open(filename, O_RDONLY);
  char linebuffer[200]; //max chars per line
  int linesize;

  //store all cites in list of char*s
  char *allcites[linecount];
  long int currcite = 0;

  while(linesize = readline(linebuffer, fd) > 0){

    allcites[currcite] = malloc(sizeof(char) * strlen(linebuffer));
    strcpy(allcites[currcite], linebuffer);
    currcite++;

    //if(currcite % 200000 == 0) printf("read line %d...\n", currcite);

  }

  //printf("finished reading %d lines, formatting...\n", currcite);

  //if dt is not already set, this will set indices arbitrarily
  //setArbitraryIndices(allcites, currcite, dt);

  return processCites(allcites, currcite, dt, citationlist);

}

void buildCSRfromCiteFile(struct CSRgraph *csr, struct DITree* dt, char *file){

  int linecount = 15000000; //best guess at how many citations (lines) are in the file - basically a buffer size

  //printf("reading...\n");

  struct Citenode *citationlist[linecount];
  initcitelist(citationlist, linecount);

  int vertexcount = readfile(file, dt, citationlist, linecount);
  //debugprintCitelist(citationlist, vertexcount);
  buildCSRfromCitearr(csr, citationlist, vertexcount);

}
