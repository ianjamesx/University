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
  
  char startVertex;
  
  cout << "Enter a vertex: ";
  cin >> startVertex;
  
  //carry out bfs search
  //keep in mind that the b-f search is a friend function, not a member of the graph object
  
  set<char> bfsResult;
  
  try{
    
    bfsResult = bfs(g, startVertex);
    
    set<char>::iterator first = bfsResult.begin();
    set<char>::iterator last = bfsResult.end();
    
    cout << "All Nodes found from Bredth-first Search:\n";
  
    writeContainer(first, last, "\n");
    
  } catch(graphError err){
    
    cout << err.what() << endl;
    
  }
  
  cout << "\n";
  
  //do a Depth-first search
  
  list<char> dfsResult;
  
  try{
    
    //note that this function is void, just pass in a list and it will
    //populate it for us
    
    //also note that the dfs does not take in a starting vertex
    
    dfs(g, dfsResult);
    
    list<char>::iterator first = dfsResult.begin();
    list<char>::iterator last = dfsResult.end();
    
    cout << "All Nodes found from Depth-first Search:\n";
    
    writeContainer(first, last, "\n");

    cout << "\n\n";
    
  } catch(graphError err){
    
    cout << err.what() << endl;
    
  }
  
  return 0;
  
}