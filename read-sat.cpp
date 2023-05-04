 // Sam Gaines
// CS 570
// Project 3
// Vertex Coloring Problem (3-SAT formula parsing)

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "read-graph.h"

using namespace std;

bool readSat(vector<vector<int>> *clauses, int *numBools, string inputFileAsString) {

    // open file
    ifstream inputFile;
    inputFile.open(inputFileAsString);
    cout << endl;
    if (!inputFile) {
        cout << "File " << inputFileAsString << " not found." << endl;
        return false;
    }

    // read number of boolean vars
    inputFile >> *numBools;

    // read clauses and store it in 2d vector
    string tempString;
    vector<int> tempIntVector;
    int x1, x2, x3;
    while (inputFile >> tempString) {
        if (tempString == "$") break;
        x1 = stoi(tempString);
        inputFile >> x2;
        inputFile >> x3;
        tempIntVector.push_back(x1);
        tempIntVector.push_back(x2);
        tempIntVector.push_back(x3);
        clauses->push_back(tempIntVector);
        tempIntVector.clear();
    }

    cout << "Input read successfully." << endl;
    return true;
}