#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "testing.h"

int main(int argc, char** argv) {
  struct Document* docs = malloc(5*sizeof(struct Document));
  get_sample_docs(docs);
  //printf("%s\n", docs[0].title);
  print_document(docs);
  return 0;
}
