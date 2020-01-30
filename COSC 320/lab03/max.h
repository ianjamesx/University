#ifndef MAX_H
#define MAX_H

#include "d_tnode.h"

template <typename T>
int findMax(tnode<T> *t){

  if (t == NULL) return -1;

  int result = t->nodeValue;
  int leftMax = findMax(t->left);
  int rightMax = findMax(t->right);

  if (leftMax > result){

    result = leftMax;

  }

  if (rightMax > result){

    result = rightMax;

  }

  return result;

}


#endif
