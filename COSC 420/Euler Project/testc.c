#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct cubeletColors{
  int x;
  int y;
  int z;
};

void print_array(int* arr, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void print_clist(struct cubeletColors clist){
  printf("%d, %d, %d\n", clist.x, clist.y, clist.z);
}

void init_array(int* arr, int n){
  int i;
  for(i = 0; i < n; i++){
    arr[i] = i;
  }
}

void swap(int *x, int *y){
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

void copy_to_colors(struct cubeletColors* clist, int* arr, int n, int i){
    clist[i].x = arr[0];
    clist[i].y = arr[1];
    clist[i].z = arr[2];
}

void permute(int *arr, int start, int end, int n){
  if(start == end){
    print_array(arr, n);
    return;
  }
  int i;
  for(i = start; i < end; i++){
    swap((arr + start), (arr + i));
    permute(arr, start + 1, end, n);
    swap((arr + i), (arr + start));
  }
}

void all_combinations(int *arr, int pos, int n, int *count, struct cubeletColors* clist) {
    const int NUM_OF_COLORS = 10;
    int i;
    if(pos < (n - 1)){
        for(i = 0; i < NUM_OF_COLORS; i++) {
            arr[pos] = i;
            all_combinations(arr, pos + 1, n, count, clist);
        }
    }else{
        for(i = 0; i < NUM_OF_COLORS; i++) {
            arr[pos] = i;
	    copy_to_colors(clist, arr, n, *count);
	    //print_clist(clist[*count]);
	    (*count)++;
        }
    }
}


void all_color_combinations(struct cubeletColors* all_color_choices, int pos, int n, struct cubeletColors* color){
    int i;
    if(pos < (n - 1)){
        for(i = 0; i < 10*10*10; i++) {
            color[pos] = all_color_choices[i];
            all_color_combinations(all_color_choices, pos + 1, n, color);
        }
    }else{
        for(i = 0; i < 10*10*10; i++) {
            color[pos] = all_color_choices[i];
	    int a;
	    for(a = 0; a < n; a++){
	      printf("%d: ", a);
	      //prints each set of 8 color combinations
	      print_clist(color[a]);
	      printf("\n");
	    }

	    //printf("%d\n", *count);
        }
    }
}

int main(int argc, char** argv){
  const int NUM_OF_COLORS = 10;
  int n = 3;//atoi(argv[1]);

  int count = 0;

  int* arr;
  arr = (int*) malloc(n*sizeof(int));

  struct cubeletColors *c;
  c = (struct cubeletColors*) malloc(NUM_OF_COLORS*NUM_OF_COLORS*NUM_OF_COLORS*sizeof(struct cubeletColors));

  all_combinations(arr, 0, n, &count, c);

  struct cubeletColors *color_choices;
  color_choices = (struct cubeletColors*) malloc(8*sizeof(struct cubeletColors));

  all_color_combinations(c, 0, 8, color_choices);
}
