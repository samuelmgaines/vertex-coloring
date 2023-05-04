// Sam Gaines
// CS 570
// Project 3
// Vertex Coloring Problem (graph parsing)

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "read-graph.h"

using namespace std;

bool readGraph(vector<vector<bool>> *g, int *v, string inputFileAsString) {

    // open file
    ifstream inputFile;
    inputFile.open(inputFileAsString);
    cout << endl;
    if (!inputFile) {
        cout << "File " << inputFileAsString << " not found." << endl;
        return false;
    }

    // read number of nodes
    inputFile >> *v;
    
    // initialize adjacency matrix to all false
    if (g->size() != 0) g->clear();
    vector<bool> tempBoolVector(*v, false);
    for (int i = 0; i < *v; i++) g->push_back(tempBoolVector);

    // read adjacency list and store it in adjacency matrix
    string tempString;
    int v1, v2;
    while (inputFile >> tempString) {
        if (tempString == "$") break;
        v1 = stoi(tempString);
        inputFile >> v2;
        g->at(v1-1).at(v2-1) = true;
        g->at(v2-1).at(v1-1) = true;
        inputFile >> tempString; // read in weight, but this is unweighted graph
    }

    cout << "Input read successfully." << endl;
    return true;
}