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
    }

    queue<vertex *> vQueue;
    start->visited = true;
    start->parent = NULL;
    start->unweightedDistance = 0;
    vQueue.push(start);

    while(!vQueue.empty()){
      vertex* ve = vQueue.front();
      vQueue.pop();
      //cout << ve->name << endl;
      for(int x = 0; x<ve->adj.size(); x++){
        if(ve->adj[x].v->visited == false){
          ve->adj[x].v->parent = ve;
          ve->adj[x].v->unweightedDistance = ve->unweightedDistance + 1;
          if(ve->adj[x].v->name == endingCity){
            //cout << "gotcha" << endl;
            //cout << ve->adj[x].v->unweightedDistance << endl;

            vertex* iterator = ve->adj[x].v;
            stack <vertex *> iteratorParent;
            while(iterator != NULL){
              iteratorParent.push(iterator);
              iterator = iterator->parent;
             }
            cout << ve->adj[x].v->unweightedDistance << ", ";
             while(iteratorParent.size()>1){
               cout << iteratorParent.top()->name << ", ";
               iteratorParent.pop();
             }
             cout << ve->adj[x].v->name << endl;
             for(int i = 0; i<vertices.size(); i++){
                 if (vertices[i].districtID == ve->adj[x].v->districtID){
                     cout << vertices[i].districtID << " " << vertices[i].name << " " << vertices[i].unweightedDistance << endl;
                 }
             }
             return;
          }
          else{
            ve->adj[x].v->visited = true;
            vQueue.push(ve->adj[x].v);
          }
        }
      }
    }


}
