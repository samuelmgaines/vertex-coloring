// Sam Gaines
// CS 570
// Project 3
// Vertex Coloring Problem (heuristic algorithm)

// This heuristic method is referred to as the DSatur method, short for degree of saturation. This method is evolved from the general
// greedy method, where vertices are colored in some order with the first available color. However, the DSatur method chooses this order
// by looking at each vertex's degree of saturation, which is the number of colors it is connected to. The vertex with the highest degree
// of saturation is chosen. In the case of a tie, the vertex with the most uncolored connected vertices (highest uncolored degree) is
// chosen. This is one of the better heuristic methods out there, and this implementation of it runs in O(V^2) time. The DSatur method
// can also be implemented in O((V + E)lgV) time, which is better than O(V^2) on average, but technically could be worse (as |E| <= |V^2|).

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <iterator>

using namespace std;

// get degree of vertex, i.e. how many edges are connected to the vertex
int degree(vector<vector<bool>> *g, int v, int vertex) {
    int d = 0;
    for (int i = 0; i < v; i++) {
        if (g->at(vertex).at(i)) d++;
    }
    return d;
}

// main function for the heuristic algorithm
int heuristic(vector<vector<bool>> *g, int v, string filename) {

    // initialize coloring array
    vector<int> color(v, 0);

    // calculate uncolored degree/saturation set of each node
    // uncolored degree counts the number of edges out of a vertex connected to uncolored vertices
    // the saturation set of a vertex contains every color the vertex is connected to
    vector<int> uncoloredDegree(v, 0);
    vector<set<int>> saturationSet;
    for (int i = 0; i < v; i++) {
        uncoloredDegree.at(i) = degree(g, v, i);
    }
    for (int i = 0; i < v; i++) {
        set<int> tempSet;
        saturationSet.push_back(tempSet);
    }

    // color all vertices
    for (int i = 0; i < v; i++) {
        // find vertex max saturation degree (uncolored degree is tiebreaker)
        int vertex = -1;
        for (int j = 0; j < v; j++) {
            // if this vertex has not been colored yet
            if (color.at(j) == 0) {
                // if we have not chosen a vertex yet
                if (vertex == -1) {
                    vertex = j;
                }
                // if the saturation degree is higher
                else if (saturationSet.at(j).size() > saturationSet.at(vertex).size()) {
                    vertex = j;
                }
                // if saturation degree is the same but uncolored degree is higher
                else if (saturationSet.at(j).size() == saturationSet.at(vertex).size() && uncoloredDegree.at(j) > uncoloredDegree.at(vertex)) {
                    vertex = j;
                }
            }
        }

        // set vertex to minimum available color
        int nextColor;
        for (nextColor = 1; nextColor < v+1; nextColor++) {
            if (saturationSet.at(vertex).find(nextColor) == saturationSet.at(vertex).end()) break;
        }
        color.at(vertex) = nextColor;

        // update saturation sets and uncolored degrees
        for (int j = 0; j < v; j++) {
            if (g->at(vertex).at(j)) {
                uncoloredDegree.at(j)--;
                saturationSet.at(j).insert(nextColor);
            }
        }
    }

    // find maximum color, which is equal to the chromatic number
    int c = 0;
    for (int i = 0; i < v; i++) {
        if (color.at(i) > c) c = color.at(i);
    }

    // annotate file with solution
    ofstream f;
    f.open(filename, ios::app);
    f << "Sam Gaines: heuristic solution (" << c << " colors):" << endl;
    for (int i = 0; i < v; i++) {
        f << "\tVertex " << i+1 << ": Color #" << color.at(i) << endl;
    }

    return c;
}