#include <iostream>
#include "d_graph.h"
#include "d_util.h"
#include <fstream>
#include <string>
#include <set>

int main(){
  
  //graph vertices consist of characters
  
  graph<char> g;
  
  //read in the graph data file
  
  ifstream graphData;
  
  graphData.open("graphA.dat");
  
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
  
  //insert edge from F to D with weight 1
  
  try{
    
     g.insertEdge('F', 'D', 1);
    
   } catch(graphError err){
      
     cout << err.what() << endl;
      
   }
   
  //remove vertex B
  
  try{
    
    g.eraseVertex('B');
   
  } catch(graphError err){
      
    cout << err.what() << endl;
      
  }
  
  //remove edge A->D
  
  try{
    
    g.eraseEdge('A', 'D');
   
  } catch(graphError err){
      
    cout << err.what() << endl;
      
  }
  
  //prompt user for vertex, list all neighbors
  
  cout << "Enter a new vertex to view its neighbors: ";
  char inputVertex;
  cin >> inputVertex;
  
  set<char> adjVert;
  
  try {
    
    adjVert = g.getNeighbors(inputVertex);
    
  } catch(graphError err){
    
    cout << err.what() << endl;
    
  }
  
  set<char>::iterator iter = adjVert.begin();
  
  if(adjVert.size() != 0) cout << "Neighbors of " << inputVertex << ": ";
  
  while(iter != adjVert.end()){
    
    cout << *iter << ", ";
    
    iter++;
    
  }
  
  cout << "\n\n";
  
  //add G to graph
  
  g.insertVertex('G');
  
  //add edges to graph
  
   try{
    
     g.insertEdge('G', 'C', 1);
     g.insertEdge('G', 'F', 1);
     g.insertEdge('D', 'G', 1);
    
   } catch(graphError err){
      
     cout << err.what() << endl;
      
   }
   
   //output graph
   
   cout << g;
 
  return 0;
  
}