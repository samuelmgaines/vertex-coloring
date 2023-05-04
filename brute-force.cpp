// Sam Gaines
// CS 570
// Project 3
// Vertex Coloring Problem (brute-force algorithm)

// This brute-force algorithm is often referred to as the backtracking method to solving the vertex coloring problem
// The backtracking method, while still not in polynomial time, is much faster than the naive brute-force method, which
// checks every possible coloring of the vertices until a valid coloring is found. The backtracking method saves time by
// "backtracking" if a certain vertex's color is invalid, rather than trying other colorings with that same error.

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
bool 

// is it valid to make "vertex" have color "potentialColor"?
isValidColor(vector<vector<bool>> *g, int v, vector<int> *color, int vertex, int potentialColor) {
    for (int i = 0; i < v; i++) {
        if (g->at(vertex).at(i) && potentialColor == color->at(i)) return false;
    }
    return true;
}

// recursive function to help with bruteForceCheck
bool bruteForceCheckHelper(vector<vector<bool>> *g, int v, vector<int> *color, int c, int vertex) {
    if (vertex == v) return true;

    // This for loop has tighter bounds than most examples online I've seen. Changing these bounds saved loads of time.
    // The intuition is, if you've gone through vertex k and tried k colors, you've definitely tried at least one unused color; why would you
    // try any others? The color chosen is arbitrary. The solution only depends on what nodes have the SAME colors, not what colors they have
    for (int i = 1; i <= vertex+1 && i <= c; i++) {
        if (isValidColor(g, v, color, vertex, i)) {
            color->at(vertex) = i;
            if (bruteForceCheckHelper(g, v, color, c, vertex + 1)) return true;
            color->at(vertex) = 0;
        }
    }
    return false;
}

// decision/NPC problem, i.e, can you produce a c-coloring?
bool bruteForceCheck(vector<vector<bool>> *g, int v, int c, string filename) {

    cout << "Checking if there is a valid " << c << "-coloring..." << endl;
    vector<int> color(v, 0);

    if (!bruteForceCheckHelper(g, v, &color, c, 0)) {
        cout << "There is not a valid " << c << "-coloring" << endl << endl;
        return false;
    }
    cout << endl;

    // annotate file if solution is found
    ofstream f;
    f.open(filename, ios::app);
    f << "Sam Gaines: brute-force solution (" << c << " colors):" << endl;
    for (int i = 0; i < v; i++) {
        f << "\tVertex " << i+1 << ": Color #" << color.at(i) << endl;
    }
    return true;
}

// main function. Find minimum chromatic number
int bruteForce(vector<vector<bool>> *g, int v, string filename) {
    int c = 1; // number of colors
    while (!bruteForceCheck(g, v, c, filename)) {
        c++;
    }
    return c;
}