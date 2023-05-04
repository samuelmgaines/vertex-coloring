// Sam Gaines
// CS 570
// Project 3
// Mapping of 3SAT to k-coloring

// A 3SAT problem can be mapped to the decision problem of "does there exist a k-coloring of given graph G". This
// mapping is implemented here.

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "read-sat.h"
using namespace std;

// get vertex corresponding to a specific boolean variable (or negation)
int getBoolVertex(int boolVar, bool truth) {
    if (truth) return 2*boolVar+1;
    else return 2*boolVar+2;
}

// get the vertex corresponding to a specific boolean variable of a specific clause
int getClauseVertex(int clause, int boolNumber, int numBools) {
    int start = 2*numBools + 1;
    int clauseStart = start + 3*clause;
    return clauseStart + boolNumber - 1;
}

int main(int argc, char **argv) {

    // ====================================================================
    // set-up
    // ====================================================================

    vector<vector<int>> clauses;
    vector<vector<bool>> g;
    int numBools;
    int v;

    // check for correct command line arguments
    if (argc != 2) {
        cout << "Usage: ./3sat-to-vc filename" << endl;
        return 0;
    }

    // read 3SAT from file
    if (!readSat(&clauses, &numBools, argv[1])) return 0;

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

    cout << endl << "This script will map the 3SAT problem of " << argv[1] << " to a " << k << "-coloring problem" << endl;

    // ====================================================================
    // map 3SAT to 3-Coloring
    // ====================================================================

    cout << endl << "Mapping the 3SAT problem to a 3-coloring problem..." << endl;

    // |V| = triangle for each var sharing one (2 * numBools + 1) + triangle for each clause (3 * clauses)
    v = 2*numBools+1 + 3*clauses.size();

    // initialize G with |V| vertices (and no edges)
    vector<bool> tempBoolVector;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            tempBoolVector.push_back(false);
        }
        g.push_back(tempBoolVector);
        tempBoolVector.clear();
    }

    // connect all triangles of bool vars
    for (int i = 0; i < numBools; i++) {
        int v1 = getBoolVertex(i, true);
        int v2 = getBoolVertex(i, false);
        g[0][v1] = true;
        g[v1][0] = true;
        g[0][v2] = true;
        g[v2][0] = true;
        g[v1][v2] = true;
        g[v2][v1] = true;
    }

    // connect all triangles of clause vars
    for (int i = 0; i < clauses.size(); i++) {
        int v1 = getClauseVertex(i, 1, numBools);
        int v2 = getClauseVertex(i, 2, numBools);
        int v3 = getClauseVertex(i, 3, numBools);
        g[v1][v2] = true;
        g[v2][v1] = true;
        g[v1][v3] = true;
        g[v3][v1] = true;
        g[v2][v3] = true;
        g[v3][v2] = true;
    }

    // connect clause vars to their corresponding literals
    for (int i = 0; i < clauses.size(); i++) {
        int c1 = getClauseVertex(i, 1, numBools);
        int c2 = getClauseVertex(i, 2, numBools);
        int c3 = getClauseVertex(i, 3, numBools);
        int v1, v2, v3;
        if (clauses[i][0] > 0) v1 = getBoolVertex(clauses[i][0], true);
        else v1 = getBoolVertex(-clauses[i][0], false);
        if (clauses[i][1] > 0) v2 = getBoolVertex(clauses[i][1], true);
        else v2 = getBoolVertex(-clauses[i][1], false);
        if (clauses[i][2] > 0) v3 = getBoolVertex(clauses[i][2], true);
        else v3 = getBoolVertex(-clauses[i][2], false);
        g[c1][v1] = true;
        g[v1][c1] = true;
        g[c2][v2] = true;
        g[v2][c2] = true;
        g[c3][v3] = true;
        g[v3][c3] = true;
    }

    cout << endl << "Mapping to 3-coloring finished" << endl;

    // ====================================================================
    // map 3-Coloring to k-coloring
    // ====================================================================

    if (k > 3) {
        cout << endl << "Mapping the 3-coloring problem to a " << k << "-coloring problem..." << endl;
    }

    int c = 3;
    while (c < k) {
        // construct a new vertex that is connected to every other vertex
        for (int i = 0; i < v; i++) {
            g[i].push_back(true);
            tempBoolVector.push_back(true);
        }
        tempBoolVector.push_back(false); // not connected to itself
        g.push_back(tempBoolVector);
        tempBoolVector.clear();
        v++; c++;
        if (c == k) {
            cout << endl << "Mapping to " << k << "-coloring finished" << endl;
        }
    }

    // ====================================================================
    // write to file
    // ====================================================================

    // get input file name (without directory and "3sat" prefix)
    stringstream ss;
    ss.str(argv[1]);
    string filename;
    while (getline(ss, filename, '/')) continue;
    if (filename.length() > 5 && filename[0] == '3' && filename[1] == 's' && filename[2] == 'a'
        && filename[3] == 't' && filename[4] == '-') {
        filename.erase(0, 1);
        filename.erase(0, 1);
        filename.erase(0, 1);
        filename.erase(0, 1);
        filename.erase(0, 1);
    }

    // add "vc-" prefix and k suffix
    filename.insert(filename.length()-4, "-k");
    filename.insert(filename.length()-4, to_string(k));
    filename.insert(0, "data/vc-");
    
    cout << endl << "Writing the vertex coloring problem to " << filename << " ..." << endl;

    // open file
    ofstream vcFile;
    vcFile.open(filename);

    vcFile << v << endl;
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if (g[i][j]) {
                vcFile << i+1 << ' ' << j+1 << " 1" << endl;
            }
        }
    }
    vcFile << '$' << endl;

    cout << endl << "Vertex coloring problem has been written to " << filename << endl;

    return 0;
}