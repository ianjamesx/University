#include<iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

//sorting algorithms

void bubbleSort(vector<int>& a);

void insertionSort(vector<int>& v);

//void mergeSort(vector<int> aVector, int size, int low, int high);
//void merge(vector<int> aVector, int size, int low, int middle, int high);

void quicksort(vector<int> &vec, int L, int R);
void swap(vector<int> &v, int x, int y);

void selectionSort(vector<int>& v);

//populate vector with random integers

void populateVector(vector<int>& v, int size);

double timeForBubble(vector<int>v);
double timeForInsertion(vector<int>v);
double timeForMerge(vector<int>v);
double timeForQuick(vector<int>v);
double timeForSelection(vector<int>v);

int main(){
  
  int size, i, j;
  
  //times
  
  double bubble, merge, insertion, quick, selection;
  
  for(i = 10; i <= 100; i+= 10){
    
    double bubble = 0.0, merge = 0.0, insertion = 0.0, quick = 0.0, selection = 0.0;
    
    for(j = 0; j < 1000; j++){
     
      vector<int>v;
      populateVector(v, i);
      
      bubble += timeForBubble(v);
      merge += timeForMerge(v);
      insertion += timeForInsertion(v);
      quick += timeForQuick(v);
      selection += timeForSelection(v);
      
    
    }
    
    //divide each by 1000 for accurate time
    
    cout << "Bubble of size " << i << " - " << (bubble /1000) << endl;
    cout << "merge of size " << i << " - " << (merge /1000) << endl;
    cout << "insertion of size " << i << " - " << (insertion /1000) << endl;
    cout << "quick of size " << i << " - " << (quick /1000) << endl;
    cout << "selection of size " << i << " - " << (selection /1000) << endl;
    
    cout << "\n\n";
    
  }
  
  for(i = 200; i <= 1000; i+= 100){
     
    double bubble = 0.0, merge = 0.0, insertion = 0.0, quick = 0.0, selection = 0.0;
    
    for(j = 0; j < 100; j++){
     
      vector<int>v;
      populateVector(v, i);
      
      bubble += timeForBubble(v);
      merge += timeForMerge(v);
      insertion += timeForInsertion(v);
      quick += timeForQuick(v);
      selection += timeForSelection(v);
      
    
    }
    
    //divide each by 1000 for accurate time
    
    cout << "Bubble of size " << i << " - " << (bubble /100) << endl;
    cout << "merge of size " << i << " - " << (merge /100) << endl;
    cout << "insertion of size " << i << " - " << (insertion /100) << endl;
    cout << "quick of size " << i << " - " << (quick /100) << endl;
    cout << "selection of size " << i << " - " << (selection /100) << endl;
    
    cout << "\n\n";
    
  }
  
  return 0;

}

double timeForBubble(vector<int>v){
  
  double start, finish, elapsed;
  
  start = double(clock())/CLOCKS_PER_SEC;
  
  bubbleSort(v);
  
  finish = double(clock())/CLOCKS_PER_SEC;
  elapsed = finish - start;
  
  return elapsed;
  
}

double timeForInsertion(vector<int>v){
  
  double start, finish, elapsed;
  
  start = double(clock())/CLOCKS_PER_SEC;
  
  insertionSort(v);
  
  finish = double(clock())/CLOCKS_PER_SEC;
  elapsed = finish - start;
  
  return elapsed;
  
}

double timeForMerge(vector<int>v){
  
  double start, finish, elapsed;
  
  start = double(clock())/CLOCKS_PER_SEC;
  
  //mergeSort(v);
  
  finish = double(clock())/CLOCKS_PER_SEC;
  elapsed = finish - start;
  
  return elapsed;
  
}

double timeForQuick(vector<int>v){
  
  double start, finish, elapsed;
  
  start = double(clock())/CLOCKS_PER_SEC;
  
  //quicksort(v, v[0], v[v.size() - 1]);
  
  finish = double(clock())/CLOCKS_PER_SEC;
  elapsed = finish - start;
  
  return elapsed;
  
}

double timeForSelection(vector<int>v){
  
  double start, finish, elapsed;
  
  start = double(clock())/CLOCKS_PER_SEC;
  
  selectionSort(v);
  
  finish = double(clock())/CLOCKS_PER_SEC;
  elapsed = finish - start;
  
  return elapsed;
  
}

void populateVector(vector<int>&v, int size){
  
  int i;
  
  for(i = 0; i < size; i++){
    
    //fill vector with random values between 1 and 100
    
    int randNum = rand()% (100-1 + 1) + 1;
    
    v.push_back(randNum);
    
  }
  
  
}

//bubble sort

void bubbleSort(vector<int>& a){
      bool swapp = true;
      while(swapp){
        swapp = false;
        for (size_t i = 0; i < a.size()-1; i++) {
            if (a[i]>a[i+1] ){
                a[i] += a[i+1];
                a[i+1] = a[i] - a[i+1];
                a[i] -=a[i+1];
                swapp = true;
            }
        }
    }
}

//insertion sort

void insertionSort(vector<int>& v){
int i, j, tmp;

 for (i=1; i< v.size(); i++)
 {
     j=i;
     tmp=v[i];
     while (j>0 && tmp<v[j-1])
     {
           v[j]=v[j-1];
           j--;
     }
     v[j]=tmp;
 }
 
}

//merge sort
/*
void merge(vector<int> aVector, int size, int low, int middle, int high){
    int temp[size];
    for(int i = low; i <= high; i++){
        temp[i] = aVector[i];
    }
    int i = low;
    int j = middle+1;
    int k = low;

    while (i <= middle && j <= high){
        if(temp[i] <= temp[j]){
            aVector[k] = temp[i];
            ++i;
        }
        else {
            aVector[k] = temp[j];
            ++j;
        }
        ++k;
    }
    while (i <= middle){
        aVector[k] = temp[i];
        ++k;
        ++i;
    }
}

void mergeSort(vector<int> aVector, int size, int low, int high){
  
  size = v.size();
  low = v[0];
  
  
    if (low < high){
        int middle = (low + high) / 2;
        mergeSort(aVector, size, low, middle);
        mergeSort(aVector, size, middle+1, high);
        merge(aVector, size, low, middle, high);
    }
}
*/
//quick sort

void quicksort(vector<int> &vec, int L, int R) {
    int i, j, mid, piv;
    i = L;
    j = R;
    mid = L + (R - L) / 2;
    piv = vec[mid];

    while (i<R || j>L) {
        while (vec[i] < piv)
            i++;
        while (vec[j] > piv)
            j--;

        if (i <= j) {
            swap(vec, i, j); //error=swap function doesnt take 3 arguments
                i++;
                j--;
        }
        else {
            if (i < R)
                quicksort(vec, i, R);
            if (j > L)
                quicksort(vec, L, j);
            return;
        }
    }
}

void swap(vector<int> &v, int x, int y) { 
    int temp = v[x];
    v[x] = v[y];
    v[y] = temp;
}

//select sort

void selectionSort(vector<int>& v){
        int temp, min;

        for( int i = 0; i < v.size(); i++){
                min = i;
                for (int j = 1; j < v.size(); j++){
                        if (v[j] < v[min])
                        min = j;
                }
                temp = v[i];
                v[i] = v[min];
                v[min] = temp;
        }
}

