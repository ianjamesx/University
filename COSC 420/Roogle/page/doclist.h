#ifndef DOCLIST
#define DOCTLIST

#include "document.h"
#include <assert.h>

#ifndef DLNODE
#define DLNODE

typedef struct DLNode {
  Doc* doc;
  struct DLNode* parent, * child;
} DLNode;

void init_DLNode(DLNode* n) {
  n->doc = NULL;
  n->parent = NULL;
  n->child = NULL;
}
void create_DLNode(DLNode* n, Doc* d) {
  init_DLNode(n);
  n->doc = d;
}

bool append(DLNode* p, DLNode* c) {
  bool noerr = true;
  if(p->child != NULL && p->child->parent != NULL) {
    //#warning Child of parent was orphaned on DocList insertion
    noerr = false;
  } else if(c->parent != NULL && c->parent->child != NULL) {
    //#warning Parent of child was left pointing to child on DocList insertion
    noerr = false;
  }
  p->child = c;
  c->parent = p;
  return noerr;
}

void print_doc_sublist(Doc* d, int n);
#endif

typedef struct DocList {
  DLNode* head, * half, * tail;
  int size;
} DocList;

void print_doclist(DocList* list) {
  assert(list->head != NULL);

  DLNode* node = list->head;
  for(int a = 0; a < list->size; a++) {
    printf("%0.4f", node->doc->id);
    if(a+1 < list->size) {
      printf(", ");
      node = node->child;
    }
  }
  puts("");
}
void init_doclist(DocList* list) {
  list->head = malloc(sizeof(DLNode));
  list->half = list->head;
  list->tail = list->head;
  list->size = 0;
}
void create_doclist(DocList* list, Doc* d) {
  init_doclist(list);
  create_DLNode(list->head, d);
  list->half = list->head;
  list->tail = list->head;
  list->size++;
}
void doclist_insert(DocList* list, Doc* d) {
  assert(list->head != NULL);

  DLNode* newnode = malloc(sizeof(DLNode));
  create_DLNode(newnode, d);

  append(list->tail, newnode);
  list->tail = list->tail->child;

  if(list->size%2 == 1)
    list->half = list->half->child;

  list->size++;
}

#endif
