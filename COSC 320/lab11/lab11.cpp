#include <iostream>
#include "d_graph.h"
#include "d_util.h"
#include <fstream>
#include <string>
#include <set>
#include <list>

int main(){
  
  //graph vertices consist of characters
  
  graph<char> g;
  
  //read in the graph data file
  
  ifstream graphData;
  
  graphData.open("graphB.dat");
  
  int vCount, eCount; //vertices and edges
  
  //first line contains all vertices we need
  
  graphData >> vCount;
  
  //we can just for loop since we know how many we need
  
  int i;
  for(i = 0; i < vCount; i++){
    
    char currVertex;
    
    graphData >> currVertex;
    
    //some error handling for good measure
    
    try{
    
      g.insertVertex(currVertex);
    
    } catch(graphError err){
      
      cout << err.what() << endl;
      
    }
    
  }
  
  //read in edges
  
  graphData >> eCount;
  
  for(i = 0; i < eCount; i++){
    
    char vStart, vEnd;
    int weight;
    
    //cout << vStart << " " << vEnd << " " << weight << endl;
    
    graphData >> vStart >> vEnd >> weight;
    
    try{
    
      g.insertEdge(vStart, vEnd, weight);
    
    } catch(graphError err){
      
      cout << err.what() << endl;
      
    }
    
  }
  
  //have user enter a vertex
  //we'll then find the minimum path value from that vertex
  
  char vStart;
  cout << "Enter a vertex: ";
  cin >> vStart;
  
  //we can use the minimumPath friend method to access this
  
  //first, we need all other vertices in the graph
  //we can do this with a regular search, lets try a bfs in this case
  
  set<char> searchResult;
  
  try {
  
    searchResult = bfs(g, vStart);
  
  } catch(graphError err){
    
    cout << err.what() << endl;
    cout << "\n";
    return 0; //just end program here
    
  }
  
  set<char>::iterator iter = searchResult.begin();
  
  //some vars to keep track of the larest path found
  
  list<char> path; //the path found
  
  char largest = *iter; //default to first
  int largestPathSize = minimumPath(g, vStart, largest, path); //the weight of the path
  
  while(iter != searchResult.end()){
    
    //for each vertex we find in the search, we want to get minimum path from vStart
    
    list<char> tempPath;
    
    int minPath = minimumPath(g, vStart, *iter, tempPath);
    
    //if its bigger than the previously largest min-path, overwrite
    
    if(minPath > largestPathSize){
      
      largestPathSize = minPath;
      path = tempPath;
      largest = *iter;
      
    }
    
    iter++;
    
  }
  
  cout << "Vertex with largest min-path: " << largest << endl;
  cout << "Total path weight: " << largestPathSize << endl;
  
  //iterate through path found
  
  list<char>::iterator pathIt = path.begin();
  cout << "Full path: ";
  
  while(pathIt != path.end()){
    
    cout << *pathIt << " ";
    pathIt++;
    
  }
  
  cout << "\n\n";
  
  return 0;
  
}