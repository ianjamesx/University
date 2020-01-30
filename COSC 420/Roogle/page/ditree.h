#ifndef DITREE
#define DITREE

#include <stdbool.h>
#include "document.h"
#include <string.h>
#include "debug.h"
#ifndef DINODE
#define DINODE

struct DINode {
  bool is_red;

  DocIndex* data;
  struct DINode* parent, *left, *right;
};

static struct DINode dinilvar = {false, NULL, NULL, NULL, NULL};
static struct DINode* const DINIL = &dinilvar;

void init_DINode(struct DINode* n, bool iR) {
  n->is_red = iR;
  n->parent = DINIL;
  n->left = DINIL;
  n->right = DINIL;
}

void create_DINode(struct DINode* n, DocIndex* di, bool iR) {
  init_DINode(n, iR);
  n->data = di;
}

void create_DINode_def(struct DINode* n, DocIndex* di) {
  create_DINode(n, di, false);
}

int DINodecmp(struct DINode* n1, struct DINode* n2) {
  return strcmp(n1->data->doc->id, n2->data->doc->id);
}

bool DINode_append_left(struct DINode* p, struct DINode* l) {
  bool noerr = true;
  if(p->left != DINIL && p->left->parent != DINIL) {
    //#warning Left child of parent was orphaned on left insertion
    noerr = false;
  } else if(l->parent != DINIL && l->parent->left != DINIL) {
    //#warning Parent of left DINode was left pointing to left DINode on left insertion
    noerr = false;
  }
  p->left = l;
  l->parent = p;
  return noerr;
}

bool DINode_append_right(struct DINode* p, struct DINode* r) {
  bool noerr = true;
  if(p->right != DINIL && p->right->parent != DINIL) {
    //#warning Right child of parent was orphaned on right insertion
    noerr = false;
  } else if(r->parent != DINIL && r->parent->right != DINIL) {
    //#warning Parent of right DINode was right pointing to right DINode on right insertion
    noerr = false;
  }
  p->right = r;
  r->parent = p;
  return noerr;
}

void DI_print_spaces(int i) {
  for(int a = 0; a < i; a++) {
    printf("    ");
  }
}
void print_subDITree_colors_recursive(struct DINode* n, int level) {
  if(n == DINIL)
    return;
  print_subDITree_colors_recursive(n->right, level+1);
  DI_print_spaces(level);
  if(n->is_red)
    //printf("R");
    printf("%s", n->data->doc->id);
  else
    printf("%s", n->data->doc->id);
    //printf("B");
  puts("");
  print_subDITree_colors_recursive(n->left, level+1);
}
void print_subDITree_values_recursive(struct DINode* n, int level) {
  if(n == DINIL)
    return;
  print_subDITree_values_recursive(n->left, level+1);
    printf("%s, ", n->data->doc->id);
  print_subDITree_values_recursive(n->right, level+1);

}
void print_subDITree_colors(struct DINode* n) {
  if(n == DINIL) {
    puts("Empty Sub DITree.");
    return;
  }
  print_subDITree_colors_recursive(n, 0);
}
#endif

struct DITree {
  struct DINode* root;
  int size;
};

void print_DITree_elements(struct DITree* tree) {
  if(tree->size < 1) {
    puts("Empty DITree.");
    return;
  }
  puts("DITree:");
  print_subDITree_values_recursive(tree->root, 0);
  puts("");
}
void print_DITree_structure(struct DITree* tree) {
  if(tree->size < 1) {
    puts("Empty DITree.");
    return;
  }
  puts("DITree:");
  print_subDITree_colors_recursive(tree->root, 0);
}
void print_DITree_debug(struct DITree* tree) {
  if(tree->root == DINIL) {
    puts("Empty.");
  }
  //printf("Tree | Size: %d, Longest Len: %d\n", tree->size, tree->longest_word);
  printf("Root: "); if(tree->root->is_red) printf("R"); else printf("B");
  printf("-%s\n", tree->root->data->doc->id);
  printf("\tLC: ");
  if(tree->root->left != DINIL) {
    if(tree->root->left->is_red)
      printf("R");
    else
      printf("B");
    printf("-%s\n", tree->root->left->data->doc->id);
  } else {
    puts("E");
  }

  printf("\t\tLC: ");
  if(tree->root->left->left != DINIL) {
    if(tree->root->left->left->is_red)
      printf("R");
    else
      printf("B");
    printf("-%s\n", tree->root->left->left->data->doc->id);
  } else {
    puts("E");
  }

  printf("\t\tRC: ");
  if(tree->root->left->right != DINIL) {
    if(tree->root->left->right->is_red)
      printf("R");
    else
      printf("B");
    printf("-%s\n", tree->root->left->right->data->doc->id);
  } else {
    puts("E");
  }

  printf("\tRC: ");
  if(tree->root->right != DINIL) {
    if(tree->root->right->is_red) printf("R"); else printf("B");
    printf("-%s\n", tree->root->right->data->doc->id);
  } else
    puts("E");
}
int DITree_populate_recursive2(struct Document* docs, int* indexes, struct DINode* node, int cnt) {
  if(node == DINIL) {
    return cnt;
  }

  docs[cnt] = *(node->data->doc);
  indexes[cnt] = node->data->matrix_index;
  cnt++;
  if(node->left != DINIL)
    cnt = DITree_populate_recursive2(docs, indexes, node->left, cnt);
  if(node->right != DINIL)
    cnt = DITree_populate_recursive2(docs, indexes, node->right, cnt);
  return cnt;
}
void DITree_convert_recursive(struct Document* docs, struct DINode* node) {
  if(node == DINIL) {
    return;
  }

  docs[node->data->matrix_index] = *(node->data->doc);
  DITree_convert_recursive(docs, node->left);
  DITree_convert_recursive(docs, node->right);
}

void DITree_populate_array(struct DITree* tree, struct Document* docs, int* indexes) {
  if(tree->size < 1) {
    return;
  }
  int cnt = 0;
  cnt = DITree_populate_recursive2(docs, indexes, tree->root, cnt);
}

void DITree_convert_to_array(struct DITree* tree, struct Document* doc_arr) {
  if(tree->size < 1) {
    return;
  }
  DITree_convert_recursive(doc_arr, tree->root);
}
void init_DITree(struct DITree* tree) {
  tree->root = malloc(sizeof(struct DINode));
  tree->size = 0;
  // tree->longest_word = -1;
}
void create_DITree(struct DITree* tree, DocIndex* di) {
  init_DITree(tree);
  create_DINode_def(tree->root, di);
  tree->size++;
  // tree->longest_word = strlen(str);
}
void define_DITree(struct DITree* tree) {
  tree->root = DINIL;
  tree->size = 0;
}

void DITree_rotater(struct DITree* tree, struct DINode* n) {
  struct DINode* nl = n->left;

  nl->parent = n->parent;
  if(n->parent == DINIL)
    tree->root = nl;
  else if(n == n->parent->right)
    n->parent->right = nl;
  else
    n->parent->left = nl;

  struct DINode* migrant = nl->right;
  n->left = migrant;
  if(migrant != DINIL) {
    migrant->parent = n;
  }
  nl->right = n;
  n->parent = nl;
}
void DITree_rotatel(struct DITree* tree, struct DINode* n) {
  struct DINode* nr = n->right;

  nr->parent = n->parent;
  if(n->parent == DINIL)
    tree->root = nr;
  else if(n == n->parent->left)
    n->parent->left = nr;
  else
    n->parent->right = nr;

  struct DINode* migrant = nr->left;
  n->right = migrant;
  if(migrant != DINIL) {
    migrant->parent = n;
  }
  nr->left = n;
  n->parent = nr;
}
void DITree_color_fix(struct DITree* tree, struct DINode* DINode) {
  struct DINode* n = DINode;
  while(n->parent->is_red) {
    if(n->parent == n->parent->parent->left) {
      struct DINode* uncle = n->parent->parent->right;
      if(uncle->is_red) {
        n->parent->is_red = false;
        uncle->is_red = false;
        n->parent->parent->is_red = true;
        n = n->parent->parent;
      } else {
        if(n == n->parent->right) {
          n = n->parent;
          DITree_rotatel(tree, n);
        }
        n->parent->is_red = false;
        n->parent->parent->is_red = true;
        DITree_rotater(tree, n->parent->parent);
      }
    } else {
      struct DINode* uncle = n->parent->parent->left;
      if(uncle->is_red) {
        n->parent->is_red = false;
        uncle->is_red = false;
        n->parent->parent->is_red = true;
        n = n->parent->parent;
      } else {
        if(DINode == DINode->parent->left) {
          n = n->parent;
          DITree_rotater(tree, n);
        }
        n->parent->is_red = false;
        n->parent->parent->is_red = true;
        DITree_rotatel(tree, n->parent->parent);
      }
    }
  }
  tree->root->is_red = false;
}
void DITree_insert_di(struct DITree* tree, DocIndex* di) {
  if(tree->root == DINIL) {
    create_DITree(tree, di);
    return;
  }
  // printf("%s\n", tree->root->data->doc->id);
  struct DINode* newptr = malloc(sizeof(struct DINode));
  create_DINode_def(newptr, di);
  struct DINode* current = tree->root;

  bool loop = current != DINIL;
  while(loop) {
    int cmp = DINodecmp(newptr, current);
    if(cmp < 0) {
      if(current->left == DINIL) {
        DINode_append_left(current, newptr);
        loop = false;
      } else
        current = current->left;
    } else if(cmp > 0) {
      if(current->right == DINIL) {
        DINode_append_right(current, newptr);
        loop = false;
      } else
        current = current->right;
    } else {
      if(debug) {
        printf("WARN: DITree Insertion Failed, {%s,%d} already exists.\n", di->doc->id, di->matrix_index);
      }
      free(newptr);
      return;
    }
    if(loop)
      loop = current != DINIL;
  }
  tree->size++;
  newptr->is_red = true;
  DITree_color_fix(tree, newptr);
}
DocIndex* DITree_insert(struct DITree* tree, struct Document* d, int index) {
  DocIndex* di; create_DocIndex(&di, d, index);
  DITree_insert_di(tree, di);
  return di;
}
int DITree_get_index(struct DITree* tree, char* query) {
  if(tree->root == DINIL || tree->size == 0) {
    return -1;
  }
  struct DINode* last = DINIL;
  struct DINode* current = tree->root;
  bool loop = true;//current != DINIL; || strcmp(current->data->doc->id, query) != 0;
  while(loop) {
    int cmp = strcmp(query, current->data->doc->id);
    if(cmp != 0) {
      last = current;
      if(cmp < 0) {
        current = current->left;
      } else if (cmp > 0) {
        current = current->right;
      }
      loop = current != DINIL;
    } else {
      return current->data->matrix_index;
    }
  }
  return -1;
}

#endif
