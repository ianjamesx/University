#include <iostream>
#include <string>
#include "d_tnode.h"
#include "buildExpTree.h"
using namespace std;

void postorder(tnode<char> *r);
void preorder(tnode<char> *r);

int main(){

  //tree 1

  tnode<char> *t1_op1 = new tnode<char>('a');
  tnode<char> *t1_op2 = new tnode<char>('b');
  tnode<char> *t1_exp1 = new tnode<char>('*', t1_op1, t1_op2);
  
  cout << "Tree 1 - Preorder ";
  preorder(t1_exp1);
  cout << "\n";
  cout << "Tree 1 - Postorder ";
  postorder(t1_exp1);
  cout << "\n";

  //tree 2

  tnode<char> *t2_op1 = new tnode<char>('a');
  tnode<char> *t2_op2 = new tnode<char>('b');
  tnode<char> *t2_op3 = new tnode<char>('c');
  tnode<char> *t2_exp1 = new tnode<char>('*', t2_op2, t2_op3);
  tnode<char> *t2_exp2 = new tnode<char>('+', t2_exp1, t2_op1);
  
  cout << "Tree 2 - Preorder ";
  preorder(t2_exp2);
  cout << "\n";
  cout << "Tree 2 - Postorder ";
  postorder(t2_exp2);
  cout << "\n";

  //tree 3

  tnode<char> *t3_op1 = new tnode<char>('a');
  tnode<char> *t3_op2 = new tnode<char>('b');
  tnode<char> *t3_op3 = new tnode<char>('c');
  tnode<char> *t3_op4 = new tnode<char>('d');
  tnode<char> *t3_op5 = new tnode<char>('e');
  tnode<char> *t3_exp1 = new tnode<char>('*', t3_op2, t3_op3);
  tnode<char> *t3_exp2 = new tnode<char>('/', t3_exp1, t3_op4);
  tnode<char> *t3_exp3 = new tnode<char>('-', t3_exp2, t3_op5);
  tnode<char> *t3_exp4 = new tnode<char>('+', t3_op1, t3_exp3);

  cout << "Tree 3 - Preorder ";
  preorder(t3_exp4);
  cout << "\n";
  cout << "Tree 3 - Postorder ";
  postorder(t3_exp4);

  return 0;

}

void postorder(tnode<char> *r){

    if (r == NULL) return;

    postorder(r->left);
    postorder(r->right);
    cout << r->nodeValue << " ";

}

void preorder(tnode<char> *r){

    if (r == NULL) return;

    cout << r->nodeValue << " ";
    preorder(r->left);
    preorder(r->right);

}
