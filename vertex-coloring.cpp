// Sam Gaines
// CS 570
// Project 3
// Vertex Coloring Problem (main)

// Suppose undirected unweighted graph G with set of edges E and vertices V. Assign a "color" to each vertex in v;
// we write color(v). Let C = {color(v): v in V}. What is min(|C|) such that color(u) != color(v) for all (u, v) in E?
// I.e., what is the least amount of colors needed to color the graph G such that no to adjacent vertices have the same
// color? We call this minimum number of colors the "chromatic number" of the graph.

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "read-graph.h"
#include "brute-force.h"
#include "heuristic.h"

using namespace std;

// ask user which solution to run
int prompt() {
    string input;
    cout << endl << "Which solution algorithm would you like to run?" << endl;
    cout << "1: Brute-force solution" << endl;
    cout << "2: Heuristic solution (approximate)" << endl;
    cout << "3: Quit" << endl;
    cin >> input;

    if (input == "1") return 1;
    else if (input == "2") return 2;
    else if (input == "3") return 3;
    else {
        cout << endl << "Please enter either 1, 2, or 3" << endl;
        return prompt();
    }
}

// print adjacency matrix (for debugging purposes)
void printGraph(vector<vector<bool>> *g, int v) {
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            cout << g->at(i).at(j) << " ";
        }
        cout << endl;
    }
    return;
}

int main(int argc, char **argv) {

    int v; // number of vertices
    vector<vector<bool>> g; // adjacency matrix
    int c = 0; // chromatic number

    // check for correct command line arguments
    if (argc != 2) {
        cout << "Usage: ./vertex-coloring.exe filename" << endl;
        return 0;
    }

    // ask which algorithm to run until prompted to stop
    int algorithmToRun = prompt();
    while (algorithmToRun != 3) {
        // read from file
        if (!readGraph(&g, &v, argv[1])) return 0;

        // perform brute-force algorithm
        if (algorithmToRun == 1) {
            cout << endl;
            cout << "Performing brute-force algorithm" << endl << endl;

            // time brute-force algorithm
            auto beg = chrono::high_resolution_clock::now();
            c = bruteForce(&g, v, argv[1]);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - beg);

            // output results
            cout << "The chromatic number of the graph is " << c << endl;
            cout << "A valid " << c << "-coloring of the graph can be found in the annotations of " << argv[1] << endl;
            if (duration.count() < 1E3) {
                cout << "This solution was found in " << duration.count() << " microseconds" << endl;
            }
            else if (duration.count() < 1E6) {
                cout << "This solution was found in " << int((duration.count()+5E2) / 1E3) << " milliseconds" << endl;
            }
            else {
                duration = chrono::duration_cast<chrono::seconds>(duration);
                cout << "This solution was found in " << int((duration.count()+5E5) / 1E6) << " seconds" << endl;
            }
        }
        // perform heuristic algorithm
        else {
            cout << endl;
            cout << "Performing heuristic algorithm..." << endl << endl;

            // time heuristic algorithm
            auto beg = chrono::high_resolution_clock::now();
            c = heuristic(&g, v, argv[1]);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - beg);

            // output results
            cout << "The chromatic number of the graph is estimated to be " << c << endl;
            cout << "A valid " << c << "-coloring of the graph can be found in the annotations of " << argv[1] << endl;
            if (duration.count() < 1E3) {
                cout << "This solution was found in " << duration.count() << " microseconds" << endl;
            }
            else if (duration.count() < 1E6) {
                cout << "This solution was found in " << int((duration.count()+5E2) / 1E3) << " milliseconds" << endl;
            }
            else {
                duration = chrono::duration_cast<chrono::seconds>(duration);
                cout << "This solution was found in " << int((duration.count()+5E5) / 1E6) << " seconds" << endl;
            }
        }
        // prompt again
        algorithmToRun = prompt();
    }
    return 0;
}