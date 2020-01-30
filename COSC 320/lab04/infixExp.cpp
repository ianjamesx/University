#include <iostream>
#include "d_tnode.h"
#include "d_tnodel.h"
#include <stack>
#include <string>

tnode<char> *infixTree(const string&);

void preorder(tnode<char> *r);

void prefixoutput(tnode<char> *exp);

int main(){
  
  string x = "a*b/c*d";
  
  tnode<char> *iftree = infixTree(x);
  
  return 0;
  
}


tnode<char> *infixTree(const string& pexp){
	// newnode is the address of the root of subtrees we build
	tnode<char> *newnode, *lptr, *rptr, *operatorNode;
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
			// current token is an operator. pop one subtrees off
			// the stack.
			lptr = s.top();
			s.pop();
		
			
			//the next one must be an operand, create a node for the operator
			//then point it to the nodes for the previous token and next token
			
			// create a leaf node and push it onto the stack
			rptr = new tnode<char>(pexp[i + 1]);
			i++; //we can also skip the next token
			
			// create a new subtree with token as root and subtees
			// lptr and rptr and push it onto the stack
			operatorNode = new tnode<char>(token,lptr,rptr);
			s.push(operatorNode);
			
			s.push(lptr);
			s.push(rptr);
			
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


void preorder(tnode<char> *r){

    if (r == NULL) return;

    cout << r->nodeValue << " ";
    preorder(r->left);
    preorder(r->right);

}


void prefixoutput(tnode<char> *exp){
  
  if (exp == NULL) return; 
  
  prefixoutput(exp->left); 
  prefixoutput(exp->right); 
  cout << exp->nodeValue << " "; 

}


infix2Postfix