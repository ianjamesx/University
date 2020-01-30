#include <iostream>
using namespace std;

bool maze(int x, int y, char m[][10], bool start);

//global maze literal for testing

char arr[5][5] =
    {
        {'1','1','1','1','1'},
        {'1','1','1','F','1'},
        {'1','0','1','1','1'},
        {'1','S','0','1','1'},
        {'1','0','1','1','1'}
    };

int main(){
  
  //read in maze from external file (use global array for testing)
  
  //first, look for 'S'
  int i, j, x, y;
  
  for(i = 0; i < 5; i++){
  
    for(j = 0; j < 5; j++){
      
      if(arr[i][j] == 'S'){
	
	x = i;
	y = j;
	
      }
      
    }
    
  }
  
  cout << "S found at " << x << ", " << y << endl;
  
  return 0;
  
}

bool maze(int x, int y, char m[][10], bool start){
  
  if(start){
    
    m[x][y] = 'X';
    
  }
  
  if(m[x][y] == 'F'){
    
    return true;
    
  }
  
  //Up
  
  if(maze(x, y-1, m, false)){
    
  }
  
  //Down
  
  if(maze(x, y + 1, m, false)){
    
  }
  
  //Left
  
  if(maze(x-1, y-1, m, false)){
    
  }
  
  //Right
  
  if(maze(x+1, y, m, false)){
    
  }
  
}