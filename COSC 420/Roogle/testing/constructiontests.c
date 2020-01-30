#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "testing.h"
#include "ditree.h"
#include "kwtree.h"
#include "debug.h"
#define DOCNUM 5
int main(int argc, char** argv) {
  struct Document docs[DOCNUM];
  get_sample_docs(docs);

/*
  DocIndex test = {"testid", 7};
  DocIndex* ptr1 = &test;
  print_DocIndex(ptr1);
  DocIndex test2 = {"testid2", 8};
  DocIndex* ptr2 = &test2;
  print_DocIndex(ptr2);
  ptr1 = ptr2;
  print_DocIndex(ptr1);
  //DocIndex* ptr3 = &({"testid3", 9});
*/
  // DocIndex arr[] = {(DocIndex) {docs[0].id, 0}, (DocIndex) {docs[1].id, 1}, (DocIndex) {docs[2].id, 2}, (DocIndex) {docs[3].id, 3}, (DocIndex) {docs[4].id, 4}};
  // struct DITree dit;
  //
  // create_DITree(&dit, &arr[0]);
  // print_DITree(&dit);
  //
  // DITree_insert_di(&dit, &arr[1]);
  // print_DITree(&dit);
  // DITree_insert_di(&dit, &arr[2]);
  // print_DITree(&dit);
  // DITree_insert_di(&dit, &arr[3]);
  // print_DITree(&dit);
  // DITree_insert_di(&dit, &arr[4]);
  // print_DITree(&dit);
  //
  // DITree_insert_di(&dit, &arr[1]);
  // print_DITree(&dit);
  //
  struct KWTree kwt;


  create_KWTree(&kwt, "testword");
  print_KWTree(&kwt);

  KWTree_insert_kw(&kwt, "abcde");
  print_KWTree(&kwt);
  KWTree_insert_kw(&kwt, "zoinks!");
  print_KWTree(&kwt);

  KWTree_insert_kw(&kwt, "word1");
  print_KWTree(&kwt);
  //KWTree_insert_kw(&kwt, "word2");
  //print_KWTree(&kwt);
  KWTree_insert_kw(&kwt, "aaaaaa");
  print_KWTree(&kwt);
  KWTree_insert_kw(&kwt, "aabaaa");
  print_KWTree(&kwt);

  KWTree_insert_kw(&kwt, "word3");
  print_KWTree(&kwt);
  KWTree_insert_kw(&kwt, "word4");
  print_KWTree(&kwt);

  KWTree_insert_kw(&kwt, "aaa");//create_KWTree(&kwt, "aaa");
  print_KWTree(&kwt);
  KWTree_insert_kw(&kwt, "aba");
  print_KWTree(&kwt);
  KWTree_insert_kw(&kwt, "bab");
  print_KWTree(&kwt);

  KWTree_insert_kw(&kwt, "aac");
  print_KWTree(&kwt);
  KWTree_insert_kw(&kwt, "bac");
  print_KWTree(&kwt);
  KWTree_insert_kw(&kwt, "bac");
  print_KWTree(&kwt);

  KWTree_insert(&kwt, "testword", 7);
  print_KWTree(&kwt);

  struct idList list;
  struct idList* buf = &list;
  KWTree_fetch_idList(&kwt, "testword", &buf);
  printlist(buf);

  KWTree_insert(&kwt, "aba", 4);
  KWTree_insert(&kwt, "aba", 2);
  KWTree_fetch_idList(&kwt, "aba", &buf);
  printlist(buf);

  return 0;
}
