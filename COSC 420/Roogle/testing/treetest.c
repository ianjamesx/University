#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "csr.h"
#include "eigen.h"
#include "dictlist.h"
#include "document.h"
//#include "rbtree.h"
#include "ditree.h"
#include "kwtree.h"
#include "treeops.h"
int main(int argc, char **argv){

  //char *str = "This is the zebra, each. word goes/ in individually, this is for how 0 as well if that makes a difference.";
  char *str = "This is the word goes/ in individually, yes/ you, or how difference 0 as well if that makes a big";
  char *str2 = "Now were at a second abstact, this one is a bit more sensible";
  char *str3 = "Specially/ we view vectors as column matrices, the matrix vector product is simply a special case of the matrix matrix product";
  char *str4 = "PageRank works by counting the number and quality of links to a page to determine a rough estimate of how important the website is. The underlying assumption is that more important websites are likely to receive more links from other websites";
  char *str5 = "Due to the huge number of items that are available or related to the query, there usually are several pages in response to a single search query as the search engine or the user's preferences restrict viewing to a subset of results per page";

  struct KWTree tree;
  struct KWTree* kwt = &tree;
  create_KWTree(kwt, "Test");
  print_KWTree(kwt);

  insertAbstract(kwt, str, 0);
  insertAbstract(kwt, str2, 1);
  insertAbstract(kwt, str3, 2);
  insertAbstract(kwt, str4, 3);
  insertAbstract(kwt, str5, 4);

  print_KWTree(kwt);

  int buffer = 1000000;
  int res[buffer];
  int ressize = getKeywordDocs(kwt, "as", res);

  int i;
  for(i = 0; i < ressize; i++){
    printf("%d \n", res[i]);
  }


  struct DITree doctree;
  struct DITree* dt = &doctree;

  DocIndex docind = {"psy/10000", 0};
  DocIndex *di = &docind;
  create_DITree(dt, di);

  DocIndex docind1 = {"cosc/43243", 2};
  DocIndex *di2 = &docind1;
  DITree_insert_di(dt, di2);

  char *psypaper = "psy/149341";
  int ind = 3;

  DocIndex docind2 = {psypaper, ind};
  DocIndex *di3 = &docind2;
  DITree_insert_di(dt, di3);

  print_DITree(dt);


/*
  printf("words to add:\n");
  for(i = 0; i < newsize; i++){
    printf("%s\n", strarr[i]);
  }
*/

/*
  int n = 5;
  int matrix[n*n];

  initMatrix(matrix, n);

  int hub[n];
  int authority[n];

  hits(matrix, authority, hub, n);

  for(i = 0; i < n; i++){
    printf("%d ", authority[i]);
  }
  printf("\nhub\n");

  for(i = 0; i < n; i++){
    printf("%d ", hub[i]);
  }

  printMatrix(matrix, n);

  struct CSRgraph graph;

  matrixtocsr(matrix, n, &graph);

  debugprint(graph);
  offsetprint(graph);

  int hub2[n];
  int auth2[n];

  sparsehit(graph, auth2, hub2, n);
  printf("\nsparse.\n");

  for(i = 0; i < n; i++){
    printf("%d ", hub2[i]);
  }

  */

  /*
  printf("\n...\n");
  struct KWTree tree;
  struct KWTree* kwt = &tree;
  create_KWTree(kwt, "This");
  print_KWTree(kwt);

  KWTree_insert_kw(kwt, "is");
  KWTree_insert_kw(kwt, "the");
  KWTree_insert_kw(kwt, "word");
  KWTree_insert_kw(kwt, "goes");
  KWTree_insert_kw(kwt, "in");
  KWTree_insert_kw(kwt, "individually");
  KWTree_insert_kw(kwt, "for");
  KWTree_insert_kw(kwt, "how");
  KWTree_insert_kw(kwt, "difference");
  KWTree_insert_kw(kwt, "0");
  KWTree_insert_kw(kwt, "as");

  print_KWTree(kwt);

  printf("inserted all words\n");
*/
/*
  int arr[50];
  int size = getWordIndexList(dt, "is", arr);

  printf("is -> ");
  for(i = 0; i < size; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
*/

  return 0;

}
