#include "Graph.h"
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <limits>


using namespace std;

Graph::Graph(){

}

Graph::~Graph(){

}

void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        //create local instance of vertex, called v
        vertex v;
        //set name property of v to n
        v.name = n;
        v.districtID = -1;
        //push the new vertex onto the verticies vector
        vertices.push_back(v);

    }
}

//adds edges to each vertex by updating the adj vector for the vertex
void Graph::addEdge(string v1, string v2, int weight){
    if (weight == -1){
      return;
    }
    //both verticies must exist in the graph to add an edge
    for(int i = 0; i < vertices.size(); i++){
        //check for v1
        if(vertices[i].name == v1){
            //if v1 found, start loop again and check for v2
            for(int j = 0; j < vertices.size(); j++){

                if(vertices[j].name == v2 && i != j){
                    //v1 and v2 are both found in verticies
                    //create an instance of adjVertex
                    adjVertex av;
                    //set the vertex pointer to point to the address of verticies[j] (v2)
                    av.v = &vertices[j];
                    //set the weight of the connection using the input value to the function
                    av.weight = weight;
                    //add to adj vector for verticies[i] (v1)
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    /*adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);*/
                }
            }
        }
    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout<< vertices[i].districtID << ":" << vertices[i].name<<"-->";
        //verticies[i].adj is a vector (can use size function)
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1){
                cout << "***";
            }
        }
        cout<<endl;
    }
}

/*
  Call this from within assignDistricts to label the districts.
  This method should implement a depth first search from the
  startingCity and assign all cities encountered the distID value.
*/
void Graph::DFSLabel(string startingCity, int distID){

    int currentDistrict = distID;
    //create stack to store address of all vertex pointers from adjacency lists
    stack <vertex *> vStack;

    //search through the vector until you find the vertex with the city name given as argunment
    for(int x = 0; x < vertices.size(); x++){
      if (vertices[x].name == startingCity){
        //set district ID and visitied properties
        vertices[x].districtID = currentDistrict;
        vertices[x].visited = true;
        //add to stack
        vStack.push(&vertices[x]);

        //check its adjacent counterparts and label them as needed
        while(vStack.size()!=0){
          vertex* ve = vStack.top();
          vStack.pop();

          for(int i = 0; i<ve->adj.size(); i++){
            if(ve->adj[i].v->visited == false){
              ve->adj[i].v->districtID = currentDistrict;
              ve->adj[i].v->visited = true;
              vStack.push(ve->adj[i].v);
            }
          }
        }
      }
    }
}

void Graph::assignDistricts(){
  //create a value to represent district number(s)
  int currentDistrict = 0;

  //search through vertices vector until a vertex with no district assigned is reached
  for(int x = 0; x < vertices.size(); x++){
    //once you reach a vertex without a district, call the DFS label function to assign it and any other cities it's connected to, to the currentDistrict value
    if (vertices[x].districtID == -1){
      currentDistrict++;
      DFSLabel(vertices[x].name, currentDistrict);
    }

  }

}

void Graph::shortestPath(string startingCity, string endingCity){
    vertex *start = NULL;
    vertex *end = NULL;
    int distance = 0;

    for (int i = 0; i<vertices.size(); i++){
      if (vertices[i].name == startingCity){
        start = &vertices[i];
      }
      else if (vertices[i].name == endingCity){
        end = &vertices[i];
      }
    }

    if((start == NULL) || (end == NULL)){
      cout << "One or more cities doesn't exist" << endl;
      return;
    }

    if (start->districtID != end->districtID){
      cout << "No safe path between cities" << endl;
      return;
    }

    for(int j = 0; j<vertices.size(); j++){
      vertices[j].visited = false;
      if (vertices[j].districtID == start->districtID){
        vertices[j].unweightedDistance = 0;
        }
      else{
          vertices[j].unweightedDistance = numeric_limits<int>::max();
      }
    }

    queue<vertex *> vQueue;
    start->visited = true;
    start->parent = NULL;
    start->unweightedDistance = 0;
    vQueue.push(start);

    while(!vQueue.empty()){
      vertex* ve = vQueue.front();
      vQueue.pop();
      if(ve->name == endingCity){
            //cout << "gotcha" << endl;
            //cout << ve->adj[x].v->unweightedDistance << endl;

            vertex* iterator = ve;
            stack <vertex *> iteratorParent;
            while(iterator != NULL){
              iteratorParent.push(iterator);
              iterator = iterator->parent;
             }
            cout << ve->unweightedDistance << ", ";
             while(iteratorParent.size()>1){
               cout << iteratorParent.top()->name << ", ";
               iteratorParent.pop();
             }
             cout << ve->name << endl;

             return;
          }
    else{
      for(int x = 0; x<ve->adj.size(); x++){

        if((ve->adj[x].v->visited == false) &&(ve->adj[x].v->districtID == end->districtID)){
          ve->adj[x].v->parent = ve;
          ve->adj[x].v->unweightedDistance = ve->unweightedDistance + 1;

            ve->adj[x].v->visited = true;
            vQueue.push(ve->adj[x].v);

        }
      }
      }
    }

}

vertex * Graph::findVertex(string name){
  vertex * found;
  for (int i = 0; i<vertices.size(); i++){
    if (vertices[i].name == name){
      found = &vertices[i];
      return found;
    }
}
  //cout << "couldn't find vertex" << endl;
  return NULL;
}

void Graph::shortestWeightedPath(string startingCity, string endingCity){
  //find start and end pointers
  vertex * start = findVertex(startingCity);
  vertex * end = findVertex(endingCity);

  if((start == NULL) || (end == NULL)){
    cout << "One or more cities doesn't exist" << endl;
    return;
  }

  if((start->districtID == -1) || (end->districtID == -1)){
    cout << "Please identify the districts before checking distances" << endl;
    return;
  }

  if (start->districtID != end->districtID){
    cout << "No safe path between cities" << endl;
    return;
  }

  for(int j = 0; j<vertices.size(); j++){
     //vertices[j].visited = false;
     if (vertices[j].districtID == start->districtID){
       vertices[j].weightedDistance = 0;
       }
     else{
         vertices[j].weightedDistance = numeric_limits<int>::max();
     }
   }

  //create solved vector
  vector<vertex *> solved;

  //set up start pointer
  start->weightedDistance = 0;
  start->parent = NULL;
  solved.push_back(start);

  //put veretex's into solved vector until end is added
  while(find(solved.begin(), solved.end(), end) == solved.end()){
    vertex* minVertex = NULL;
    //set minDist to a value that can be negated
    int minDist = numeric_limits<int>::max();
    //go through vertex's in solved array
    for(int i = 0; i < solved.size(); i++){
      //go through solved[i]'s adjacency list
      for(int j = 0; j < solved[i]->adj.size(); j++){
        //check if adjacent vertex has been solved already (is in solved vector)
        if(find(solved.begin(), solved.end(), solved[i]->adj[j].v) == solved.end()){
          int dist = 0;
          //add up weghtedDistance of current adj veretex
          vertex* iterator = solved[i];
          //while(iterator != NULL){
            dist = iterator->weightedDistance;
            //iterator = iterator->parent;
        //  }
          dist += solved[i]->adj[j].weight;

          //check if dist is less than minDist
          if(dist < minDist){
            solved[i]->adj[j].v->parent = solved[i];
            solved[i]->adj[j].v->weightedDistance = dist;
            minVertex = solved[i]->adj[j].v;
            minDist = dist;

          }
        }
      }
    }
    solved.push_back(minVertex);
  }

  vertex* it = end;
  stack <vertex *> itParent;
  while(it != NULL){
    itParent.push(it);
    it = it->parent;
   }
  cout << end->weightedDistance << ", ";
   while(itParent.size()>1){
     cout << itParent.top()->name << ", ";
     itParent.pop();
   }
   cout << end->name << endl;

return;
}
