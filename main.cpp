#include "Graph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;


int main(int argc, char *argv[]){
  //create class object
  Graph object;
  //open file for input
  ifstream myFile;
  //open file for input a second time
  ifstream myFile2;

  myFile.open(argv[1]);
  myFile2.open(argv[1]);

  //check that file opens properly
  if (!myFile){
    cout<< "file did not open" << endl;
    return -1;
  }

  //add vertex
  string line;
  int i = 0;
  //get each line from the file, skip the first line using i
  while(getline(myFile, line)){
    i++;
    if (i>1){
      //put line into stringstream to use getline on each line from file
      stringstream ss;
      ss << line;
      //store each part of the line
      string item;

      string name;

      //call getline once to get the city name from the line (first word on the line)
      getline(ss, item, ',');
      name = item;
      //add vertex with the new city name
      object.addVertex(name);
    }

  }


  //add each edge to each vertex
  i = 0;
  //create a string vector to store each city name in a vector
  vector<string> v2;

  while(getline(myFile2, line)){

    //if i is less than 1, we are on the first line of the file with all the city names and these must be stored in the v2 vector
    if(i<1){

      //turn line into a string stream to parse the line with getline
      stringstream ss;
      ss << line;

      string adjCity;
      //increment through each line and store each city name in the v2 vector
      int j = 0;
      while(getline(ss, adjCity, ',')){
        //skip the first word ("cities") and store all the city names
        if (j>0){
        v2.push_back(adjCity);
        }
        j++;
      }
    }
    i++;

    //if i is greater than 0, we have passed the first line of the file and have the lines with the connections and weights
    if(i>1){
      //turn line into string stream
      stringstream ss;
      ss << line;

      string item;
      string city1;

      //increment through each item in the line and store each connection in the edge vector using add edge for the current city
      int j = 0;
      int c;
      while(getline(ss, item, ',')){
        //if j = 0, we are on the first item in the line with is the city name that we are finding the connections for so store this item
        if(j == 0){
          city1 = item;
        }
        //we are passed the first item in the line, we have reached the connections and weights
        else{
        int weight = stoi(item);
        c = j-1;
        //call addEdge with the city name and the city associated with the current connection/weight (v2[c])
        if (weight != -1)  
        object.addEdge(city1, v2[c], weight);

      }
      j++;
      }
    }
    }

    int choice = 0;
    while (choice != 5){
      cout << "======Main Menu======" << endl;
      cout << "1. Print vertices" << endl;
      cout << "2. Find districts" << endl;
      cout << "3. Find shortest path" << endl;
      cout << "4. Find shortest weighted path" << endl;
      cout << "5. Quit" << endl;


    cin >> choice;

    if (choice == 1){
      //print verticies
      object.displayEdges();
    }
    if (choice == 2){
      object.assignDistricts();
    }
    if (choice == 3){
      string start;
      cin.ignore(1,'\n');
      cout << "Enter first city: " << endl;
      getline(cin, start);
      string end;
      cout << "Enter second city: " << endl;
      getline(cin, end);
      object.shortestPath(start, end);
    }

    if (choice == 4){
      string start;
      cin.ignore(1,'\n');
      cout << "Enter first city: " << endl;
      getline(cin, start);
      string end;
      cout << "Enter second city: " << endl;
      getline(cin, end);
      object.shortestWeightedPath(start, end);
    }
  }
  return 0;
}
