#ifndef CUSTOMMPITYPES
#define CUSTOMMPITYPES
#include <mpi.h>
#include <stddef.h>
#include "debug.h"
#include "kwtree.h"
#include "document.h"

//MPI_DataType MPI_DINode;
MPI_Datatype MPI_DOC;
int define_custom_document() {
  //(char*, )
  int count = 6;
  const MPI_Aint displacement[] = {offsetof(struct Document, id), offsetof(struct Document, title), offsetof(struct Document, authors), offsetof(struct Document, abstract), offsetof(struct Document, matrixindex), offsetof(struct Document, hubscore)};
  const int block_length[] = {MAXDOCIDLEN, MAXDOCTITLELEN, MAXDOCAUTHORSLEN, MAXDOCABSTRACTLEN, 1, 3};
  const MPI_Datatype types[] = {MPI_CHAR, MPI_CHAR, MPI_CHAR, MPI_CHAR, MPI_INT, MPI_FLOAT};
  int ret = MPI_Type_create_struct(6, block_length, displacement, types, &MPI_DOC);
  MPI_Type_commit(&MPI_DOC);
  return ret;
}

void define_custom_types() {
  define_custom_document();
}

#endif
