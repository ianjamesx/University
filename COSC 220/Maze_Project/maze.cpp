#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

/*

Notice use of vectors rather than 2d arrays

There is one major problem with using arrays for this project

arrays require the second dimmensional parameter to have the number
of indexes so the compiler knows when to split the memory, for example,
maze definiton would look similar to the following:

maze(x, y, arr[][10]...);

this will not work as the text file determines second dimmension size

so, vectors are used rather than arrays, as size is easily modifiable

*/

bool maze(int x, int y, vector<vector<char> > &m, bool start, bool skip);
void printMaze(vector<vector<char> > m);
void readOutSol(vector<vector<char> > m);

int main(){

  //skip will be used to either view search step by step or skip to end
  //if user opts to see each step, they'll have to press enter in between each step

  bool skip = false;

  //read in maze from external file

  ifstream infile("maze123.txt");
  ifstream counter("maze123.txt");

  //first, read number of lines in file

  string fileLine;

  cout << "Verifying maze column and row length...\n";

  int lineCount, charCount;

  while(getline(counter, fileLine)){

    lineCount++;

    //to get character count in a line, take length of line, divide by two to account for spaces
    //but add 1 since integer division will round down one value
    charCount = (fileLine.length() / 2) + 1;

  }

  //cout << "Rows: " << lineCount << ", Columns: " << charCount << "\n\n";

  if(lineCount != charCount){

    cout << "Warning: This is not a valid maze, the number of rows is different from number of columns" << endl;
    cout << "Please check the maze for any errors" << endl;
    cout << "Press Enter to search anyway" << endl;
    cin.get();

  }

  //keep track of maze

  vector<vector<char> > m(lineCount);

  char element;
  int row = 0, col = 0;
  while (infile >> element){

    m[row].push_back(element);

    col++;
    if(col >= charCount){

      col = 0;
      row++;

    }

  }

  //first, look for 'S' (starting point)

  int i, j, x, y;

  for(i = 0; i < m.size(); i++){

    for(j = 0; j < m[i].size(); j++){

      if(m[i][j] == 'S'){

        cout << "Starting point found\n\n";

	      x = i;
	      y = j;

      }

    }

  }

  cout << "Here is the maze we will be searching:\n";
  printMaze(m);

  char input;
  bool valid = false;

  cout << "\n\nWould you like to see search step by step or skip to final path?\n" <<
          "Enter 'Y' to see maze search step by step, or 'N' to skip to final path:";

  do {

    cin >> input;

    if(input == 'Y' || input == 'y'){

      valid = true;
      skip = false;

    } else if(input == 'N' || input == 'n'){

      valid = true;
      skip = true;

    } else {

      cout << "Invalid input, try again\n";

    }

  } while(!valid);

  if(maze(x, y, m, true, skip)){

    cout << "Path found!\nFinal Path:\n";

    //when showing final path, turn starting point back to 'S' from 'X'

    m[x][y] = 'S';
    printMaze(m);

    cout << "\n\nWriting maze to external file...";

    readOutSol(m);

    cout << " Success!\n\n\n";

  } else {

    cout << "We could not find a path! It is assumed no path exists" << endl;
    cout << "\n\nMaze path will not be written to external file" << endl;

  }

  return 0;

}

bool maze(int x, int y, vector<vector<char> > &m, bool start, bool skip){

  //out of bounds
  //note, for y boundary, check subvector at index x

  if(x < 0 || y < 0 || x > (m.size() - 1) || y > (m[x].size() - 1)){

    return false;

  }

  //hit an X or a 0

  if(m[x][y] == 'X' || m[x][y] == '0'){

    return false;

  }

  //reach the end

  if(m[x][y] == 'F'){

    return true;

  }

  //valid path (or starting)

  if(m[x][y] == '1' || start){

    m[x][y] = 'X';

    //only print the maze and give option to continue
    //if the search finds a valid path
    //and user opted not to skip

    if(!skip){

      cout << "Press Enter to continue searching...";
      cin.get();
      printMaze(m);

    }

  }

  //Up

  if(maze(x-1, y, m, false, skip)){

    return true;

  }

  //Down

  if(maze(x+1, y, m, false, skip)){

    return true;

  }

  //Left

  if(maze(x, y-1, m, false, skip)){

    return true;

  }

  //Right

  if(maze(x, y+1, m, false, skip)){

    return true;

  }

  /////////////////
  //diagonals

  /*

  if(maze(x-1, y+1, m, false, skip)){

    return true;

  }

  if(maze(x+1, y+1, m, false, skip)){

    return true;

  }

  if(maze(x+1, y-1, m, false, skip)){

    return true;

  }

  if(maze(x-1, y-1, m, false, skip)){

    return true;

  }

  */

  //////////////////

  return false;

}

void printMaze(vector<vector<char> > m){

  int i, j;

  cout << "\n";

  for(i = 0; i < m.size(); i++){

    for(j = 0; j < m[i].size(); j++){

      cout << m[i][j] << " ";

    }

    cout << endl;

  }

  cout << "\n";

}

void readOutSol(vector<vector<char> > m){

  //open file

  ofstream outfile("sol123.txt");

  //read out

  int i, j;

  for(i = 0; i < m.size(); i++){

    for(j = 0; j < m[i].size(); j++){

      outfile << m[i][j] << " ";

    }

    outfile << '\n';

  }

}
