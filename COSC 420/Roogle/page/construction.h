#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <mpi.h>
#include <assert.h>
#include "debug.h"
#include "document.h"
#include "kwtree.h"
#include "ditree.h"

int parse_into_KWTree(struct KWTree* tree, char* abstract, int index) {
  int start = 0; int next;
  int len = strlen(abstract);
  // printf("%s\n", abstract);
  for(int next = start+1; next < len; next++) {
    if((abstract[next] == ' ' || abstract[next] == '\0' || abstract[next] == ',' || abstract[next] == '.' || abstract[next] == '-')) {
      int wordlen = next-start;
      if(wordlen > 4) {
        if(abstract[start] == ' ') {
          start++;
          wordlen = next-start;
        }
        //char* word[wordlen];
        char* word = malloc(wordlen*sizeof(char));
        memcpy(word, abstract+start, wordlen);
        //word[wordlen] = '\0';
        if(strcmp(word, "with") != 0 && strcmp(word, "which") != 0 && strcmp(word, "well") != 0 && strcmp(word, "that") != 0 && strcmp(word, "such") != 0 && strcmp(word, "from") != 0) {
          // printf("%s %d %d\n", word, start, next);
          // for(int i = 0; i < strlen(word); i++) {
          //   printf("%d, ", word+i);
          // }
          //puts("");
          KWTree_insert(tree, word, index);
          //puts("Inserted.");
        }
        next++;
        start=next;
      } else {
        next++;
        start=next;
      }
    }
  }
  // puts("Done.");
}
