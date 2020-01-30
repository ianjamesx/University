#include <iostream>
#include "countOneChild.h"
#include "max.h"
#include "d_tnode.h"
using namespace std;

tnode<char> *buildTree();

int main(){
  
  tnode<char> *root = buildTree();
  
  int count = oneChildNodes(root);
  
  cout << "One-Child Node Total: " << count << endl;
  
  return 0;
  
}

tnode<char> *buildTree(){
  
  // 9 tnode pointers; points to the 9 items in the tree
  tnode<char> *root, *b, *c, *d, *e, *f, *g, *h, *i;

  g = new tnode<char> ('G');
  h = new tnode<char> ('H');
  i = new tnode<char> ('I');
  d = new tnode<char> ('D');
  e = new tnode<char> ('E',g, (tnode<char> *)NULL);
  f = new tnode<char> ('F',h, i);
  b = new tnode<char> ('B',d, e);
  c = new tnode<char> ('C',(tnode<char> *)NULL, f);
  root = new tnode<char> ('A',b, c);

  return root;
}