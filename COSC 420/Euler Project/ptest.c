#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_array(int* arr, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
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

void all_combinations(int *arr, int pos, int n, int colours) {
    int i;
    if(pos < (n - 1)){
        for(i = 0; i < colours; i++) {
            arr[pos] = i;
            all_combinations(arr, pos + 1, n, colours);
        }
    }else{
        for(i = 0; i < colours; i++) {
            arr[pos] = i;
            print_array(arr, n);
        }
    }
}

int main(int argc, char** argv){
  int n = atoi(argv[1]);

  int* arr;
  arr = (int*) malloc(n*sizeof(int));

  all_combinations(arr, 0, n, 2);

  //init_array(arr, n);

  //permute(arr, 0, n, n);
}
