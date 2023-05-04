// Sam Gaines
// CS 570
// Project 3
// Mapping of k-Coloring to 3SAT

// The decision problem of "does there exist a k-coloring of given graph G" can be mapped to a 3SAT problem. This
// mapping is implemented here.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "read-graph.h"
using namespace std;

// prints every clause (for debugging purposes)
void printClauses(vector<vector<int>> clauses) {
    for (int i = 0; i < clauses.size(); i++) {
        for (int j = 0; j < clauses[i].size(); j++) {
            if (j != 0) cout << " or ";
            cout << clauses[i][j];
        }
        cout << endl;
    }
}

int main(int argc, char **argv) {

    // ====================================================================
    // set-up
    // ====================================================================

    int v; // number of vertices
    vector<vector<bool>> g; // adjacency matrix

    // check for correct command line arguments
    if (argc != 2) {
        cout << "Usage: ./vc-to-3sat filename" << endl;
        return 0;
    }

    // read graph from file
    if (!readGraph(&g, &v, argv[1])) return 0;

    // get value of k (k-coloring)
    int k;
    cout << endl << "k = ";
    cin >> k;

    while (k < 3) {
        cout << endl << "The k-coloring problem is NP Complete only when k is at least 3" << endl;
        cout << "Please enter a k >= 3" << endl;
        cout << endl << "k = ";
        cin >> k;
    }

    cout << endl << "This script will map the " << k << "-coloring problem of " << argv[1] << " to a 3SAT problem" << endl;

    // initialize 3SAT variables
    vector<vector<int>> x; // numbering of boolean variables x[i][j], i in {1,...,|V|}, j in {1,...,k}
    int boolCounter = 1;
    vector<int> tempIntVector;
    for (int i = 0; i < v; i++) {
        for (int i = 0; i < k; i++) {
            tempIntVector.push_back(boolCounter);
            boolCounter++;
        }
        x.push_back(tempIntVector);
        tempIntVector.clear();
    }

    // initialize SAT output vector
    vector<vector<int>> clauses;

    // ====================================================================
    // mapping vc to sat
    // ====================================================================

    cout << endl << "Mapping the " << k << "-coloring problem to a SAT problem..." << endl;

    // at MOST one color assigned to each node
    for (int i = 0; i < v; i++) {
        for (int color1 = 0; color1 < k; color1++) {
            for (int color2 = color1+1; color2 < k; color2++) {
                tempIntVector.push_back(-x[i][color1]);
                tempIntVector.push_back(-x[i][color2]);
                clauses.push_back(tempIntVector);
                tempIntVector.clear();
            }
        }
    }

    // at LEAST one color assigned to each node 
    for (int i = 0; i < v; i++) {
        for (int color = 0; color < k; color++) {
            tempIntVector.push_back(x[i][color]);
        }
        clauses.push_back(tempIntVector);
        tempIntVector.clear();
    }

    // if (v1, v2) in G, then color(v1) != color(v2)
    for (int v1 = 0; v1 < v; v1++) {
        for (int v2 = v1+1; v2 < v; v2++) {
            if (g[v1][v2]) {
                for (int color = 0; color < k; color++) {
                    tempIntVector.push_back(-x[v1][color]);
                    tempIntVector.push_back(-x[v2][color]);
                    clauses.push_back(tempIntVector);
                    tempIntVector.clear();
                }
            }
        }
    }

    cout << endl << "Mapping to SAT finished" << endl;

    // ====================================================================
    // mapping sat to 3sat
    // ====================================================================

    cout << endl << "Mapping general SAT problem to 3SAT problem..." << endl;

    // initialize another SAT output vector (for 3SAT only this time)
    vector<vector<int>> clauses2;

    // initialize SAT bools that will always be TRUE in a solution
    vector<int> newBools;

    // change SAT clauses to 3SAT clauses
    for (int i = 0; i < clauses.size(); i++) {

        // if SAT clause has 1 bool var -> (x | T | T) & (x | F | F) & (x | T | F) & (x | F | T)
        if (clauses[i].size() == 1) {
            while (newBools.size() < 2) {
                newBools.push_back(boolCounter);
                boolCounter++;
            }
            tempIntVector.push_back(clauses[i][0]);
            tempIntVector.push_back(newBools[0]);
            tempIntVector.push_back(newBools[1]);
            clauses2.push_back(tempIntVector);
            tempIntVector[1] *= -1;
            clauses2.push_back(tempIntVector);
            tempIntVector[2] *= -1;
            clauses2.push_back(tempIntVector);
            tempIntVector[1] *= -1;
            clauses2.push_back(tempIntVector);
            tempIntVector.clear();
        }

        // if SAT clause has 2 bool var -> (x1 | x2 | T) & (x1 | x2 | F)
        else if (clauses[i].size() == 2) {
            while (newBools.size() < 1) {
                newBools.push_back(boolCounter);
                boolCounter++;
            }
            tempIntVector.push_back(clauses[i][0]);
            tempIntVector.push_back(clauses[i][1]);
            tempIntVector.push_back(newBools[0]);
            clauses2.push_back(tempIntVector);
            tempIntVector[2] *= -1;
            clauses2.push_back(tempIntVector);
            tempIntVector.clear();
        }

        // if SAT clause already has 3 bool vars -> do nothing
        else if (clauses[i].size() == 3) {
            clauses2.push_back(clauses[i]);
        }

        // if SAT clause has > 3 bool vars -> (x1 | x2 | n1) & (x3 | -n1 | n2) & ...
        else if (clauses[i].size() > 3) {
            tempIntVector.push_back(clauses[i][0]);
            tempIntVector.push_back(clauses[i][1]);
            tempIntVector.push_back(boolCounter);
            newBools.push_back(boolCounter);
            clauses2.push_back(tempIntVector);
            boolCounter++;
            for (int j = 0; j < clauses[i].size() - 4; j++) {
                tempIntVector[0] = clauses[i][j+2];
                tempIntVector[1] = -tempIntVector[2];
                tempIntVector[2] = boolCounter;
                newBools.push_back(boolCounter);
                clauses2.push_back(tempIntVector);
                boolCounter++;
            }
            tempIntVector[0] = clauses[i][clauses[i].size() - 2];
            tempIntVector[1] = clauses[i][clauses[i].size() - 1];
            tempIntVector[2] *= -1;
            clauses2.push_back(tempIntVector);
            tempIntVector.clear();
        }
    }

    cout << endl << "Mapping to 3SAT finished" << endl;

    // ====================================================================
    // write to file
    // ====================================================================

    // get input file name (without directory and "vc" prefix)
    stringstream ss;
    ss.str(argv[1]);
    string filename;
    while (getline(ss, filename, '/')) continue;
    if (filename.length() > 3 && filename[0] == 'v' && filename[1] == 'c' && filename[2] == '-') {
        filename.erase(0, 1);
        filename.erase(0, 1);
        filename.erase(0, 1);
    }

    // add "3sat" prefix and k suffix
    filename.insert(filename.length()-4, "-k");
    filename.insert(filename.length()-4, to_string(k));
    filename.insert(0, "data/3sat-");
    
    cout << endl << "Writing the 3SAT problem to " << filename << " ..." << endl;

    // open file
    ofstream satFile;
    satFile.open(filename);

    // write clauses to file
    satFile << boolCounter-1 << endl;
    for (int i = 0; i < clauses2.size(); i++) {
        for (int j = 0; j < clauses2[i].size(); j++) {
            if (j != 0) satFile << " ";
            satFile << clauses2[i][j];
        }
        satFile << endl;
    }
    satFile << "$" << endl;

    cout << endl << "3SAT problem has been written to " << filename << endl;
    
    return 0;
}