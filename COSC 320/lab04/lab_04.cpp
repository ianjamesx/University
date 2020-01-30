#include <iostream>
#include "d_tnode.h"
#include <string>
#include <stack>
using namespace std;

tnode<char> *buildExpTree(const string&);
void prefixoutput(tnode<char> *exp);

void preorder(tnode<char> *r);

int main(){
  
  tnode<char> *post;
  
  string postfix = "ab*cd/+";
  post = buildExpTree(postfix);
  cout << "Prefix expression: ";
  preorder(post);
  
  cout << "\n";
  
  //reusing tree 2 from part 1
  
  tnode<char> *t2_op1 = new tnode<char>('a');
  tnode<char> *t2_op2 = new tnode<char>('b');
  tnode<char> *t2_op3 = new tnode<char>('c');
  tnode<char> *t2_exp1 = new tnode<char>('*', t2_op2, t2_op3);
  tnode<char> *t2_exp2 = new tnode<char>('+', t2_exp1, t2_op1);
  
  cout << "Prefix expression: ";
  
  prefixoutput(t2_exp2);
  
  cout << "\n";
  
  return 0;
  
}

tnode<char> *buildExpTree(const string& pexp){
	// newnode is the address of the root of subtrees we build
	tnode<char> *newnode, *lptr, *rptr;
	char token;
	// subtrees go into and off the stack
	stack<tnode<char> *> s;
	int i = 0;

	// loop until i reaches the end of the string
	while(i != pexp.length())
	{
		// skip blanks and tabs in the expression
		while (pexp[i] == ' ' || pexp[i] == '\t')
			i++;

		// if the expression has trailing whitespace, we could
		// be at the end of the string
		if (i == pexp.length())
			break;

		// extract the current token and increment i
		token = pexp[i];
		i++;

		// see if the token is an operator or an operand
		if (token == '+' || token == '-' || token == '*' || token == '/')
		{
			// current token is an operator. pop two subtrees off
			// the stack.
			rptr = s.top();
			s.pop();
			lptr = s.top();
			s.pop();
		
			// create a new subtree with token as root and subtees
			// lptr and rptr and push it onto the stack
			newnode = new tnode<char>(token,lptr,rptr);
			s.push(newnode);
		}
		else // must be an operand
		{
			// create a leaf node and push it onto the stack
			newnode = new tnode<char>(token);
			s.push(newnode);
		}
	}

	// if the expression was not empty, the root of the expression
	// tree is on the top of the stack
	if (!s.empty())
		return s.top();
	else
		return NULL;
}

void prefixoutput(tnode<char> *exp){
  
  if (exp == NULL) return; 
  
  prefixoutput(exp->left); 
  prefixoutput(exp->right); 
  cout << exp->nodeValue << " "; 

}

void preorder(tnode<char> *r){

    if (r == NULL) return;

    cout << r->nodeValue << " ";
    preorder(r->left);
    preorder(r->right);

}

