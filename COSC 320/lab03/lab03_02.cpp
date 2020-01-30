#include <iostream>
#include "countOneChild.h"
#include "max.h"
#include "d_tnode.h"
using namespace std;

tnode<int> *buildTree();

int main(){
  
  tnode<int> *root = buildTree();
  
  int count = findMax(root);
  
  cout << "Max Node Value: " << count << endl;
  
  return 0;
  
}

tnode<int> *buildTree(){
  
  // 9 tnode pointers; points to the 9 items in the tree
  tnode<int> *root, *b, *c, *d, *e, *f;

  
  d = new tnode<int> (12);
  e = new tnode<int> (5);
  f = new tnode<int> (48);
  b = new tnode<int> (40, e);
  c = new tnode<int> (15, f, d);
  root = new tnode<int> (35, b, c);

  return root;
}