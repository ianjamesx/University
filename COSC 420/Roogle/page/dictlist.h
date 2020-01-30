
struct idNode {
  int index;
  struct idNode *next;
};

struct idList {
  struct idNode *first;
  struct idNode *last;
  int size;
};

void initlist(struct idList *list){
  //list = (struct idList*)malloc(sizeof (struct idList));
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
}

void appendtolist(struct idList *list, int index){
  //create first node in list
  if(list == NULL){
    initlist(list);
  }
  if(list->first == NULL){
    list->first = (struct idNode*)malloc(sizeof (struct idNode));
    list->first->index = index;
    list->last = list->first;
    list->size++;
    return;
  }
  //append to last node
  list->last->next = (struct idNode*)malloc(sizeof (struct idNode));
  list->last->next->index = index;
  list->last = list->last->next;
  list->size++;
}
void append_sublist(struct idList* parent, struct idList* child) {
  if(child == NULL)
    return;
  if(parent == NULL || parent->size == 0) {
    parent->first = child->first;
    parent->last = child->last;
    parent->size = child->size;
    return;
  }
  // printf("%d", parent->last->next == NULL);
  // for(int i = 0 ; i < child->size; i++) {
  //   appendtolist(parent, -1);
  // }

  //parent->last->next = (struct idNode*) malloc(sizeof(struct idNode));
  // printf("%d\n", parent->size);
  // printf("hello: %d \n", parent->last == NULL);

  parent->last->next = child->first;
  parent->last = child->last;
  parent->size += child->size;
}

void create_from_array(struct idList* list, int* arr, int n) {
  initlist(list);
  for(int i = 0; i < n; i++) {
    appendtolist(list, arr[i]);
  }
}

void printlist(struct idList *list){
  struct idNode *curr = list->first;
  while(curr != NULL){
    printf("%d, ", curr->index);
    curr = curr->next;
  }
  printf("\n");
}

int convertToArr(struct idList *list, int arr[]){

  int i;
  struct idNode *curr = list->first;

  for(i = 0; i < list->size; i++) {
    arr[i] = curr->index;
    curr = curr->next;
  }
  return i;
}

void shift_list_indicies(struct idList* list, const int delta) {
  struct idNode* curr = list->first;
  for(int i = 0; i < list->size; i++) {
    curr->index += delta;
    curr = curr->next;
  }
}
void freelist(struct idList *list){
  struct idNode *curr = list->first;
  while(curr != NULL){
    struct idNode *temp = curr;
    curr = curr->next;
    free(temp);
  }
  free(list);
}
