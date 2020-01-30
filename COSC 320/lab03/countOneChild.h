#ifndef COUNTONECHILD_H
#define COUNTONECHILD_H

#include "d_tnode.h"

template <typename T>
int oneChildNodes(tnode<T> *t){

  int count = 0;

  if(t == NULL) return count;

  if((t->left == NULL && t->right != NULL) || (t->left != NULL && t->right == NULL)){

    count++;

  }

  count += (oneChildNodes(t->left) + oneChildNodes(t->right));

  return count;

}



#endif
