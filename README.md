# Sam Gaines - Vertex Coloring Project

## Project Description

### Vertex Coloring Problem

The Vertex Coloring problem (or k-coloring problem) is an NP-Complete problem that poses the following question:

Given undirected graph $G = (V, E)$ with unweighted edges, does there exist an assignment of at
most $k$ colors to the vertices such that $color(u) \neq color(v) \forall (u, v) \in E$?

### Brute-force and Heuristic Algorithms

A brute-force algorithm for an NP-Complete problem is one that will always find the correct answer but does not run in polynomial time.

A heuristic algorithm for an NP-Complete problem, on the other hand, will run in polynomial time, but is not always definitively correct. It instead provides an estimate.

### NP-Complete Mappings

NP-Complete problems are problems that are in NP, but are at least as hard as every other problem in NP. This means that there is a way to map any NP-Complete problem to any other NP-Complete problem in polynomial time. 3-SAT and Vertex Coloring are two NP-Complete problems, so there is a polynomial-time mapping from 3-SAT to Vertex Coloring and vice versa.

### Project Scope
This project offers four functions:
  1. A brute-force solution to the Vertex Coloring Problem (the backtracking algorithm)
  2. A heuristic solution to the Vertex Coloring Problem (the DSatur heuristic)
  3. A mapping from the Vertex Coloring Decision Problem to 3-SAT
  4. A mapping from 3-SAT to the Vertex Coloring Decision Problem

A C++ script was used to implement each of these.

A more detailed analysis of this project's algorithms and results can be found in `paper.pdf`.

## Overview

### C++ Scripts

The main interface for the first two functions of this project can be found in `vertex-coloring.cpp`, which makes calls to `read-graph`, `brute-force.cpp`, and `heuristic.cpp` as necessary.

`read-graph.cpp` provides the functionality for parsing the input graph and providing an adjacency matrix. `brute-force.cpp` and `heuristic.cpp` provide the functionality for the brute-force and heuristic algorithm, respectively.

`3sat-to-vc.cpp` is the script for mapping a 3-SAT problem to a Vertex Coloring problem. It makes use of `read-sat.cpp`, which provides the functionality for parsing the input 3-SAT problem and providing a list of clauses.

`vc-to-3sat.cpp` is the script for mapping a Vertex Coloring problem to a 3-SAT problem. It makes use of `read-graph.cpp`, discussed above.

### Given Input Files
 - `data/3sat-ejyohannan-hard-3sat.dat`: 3-SAT problem provided by EJ Yohannan that fails on his 3-SAT heuristic
 - `data/3sat-ejyohannan-intractable-3sat.dat`: 3-SAT problem provided by EJ Yohannan that is intractable for his 3-SAT brute-force algorithm
 - `data/3sat-hc-k3.dat`: 3-SAT problem resulting from a mapping of the 3-coloring problem `vc-hc.dat`
 - `data/3sat-hc-k4.dat`: 3-SAT problem resulting from a mapping of the 4-coloring problem `vc-hc.dat`
 - `data/3sat-intractable-random-graph-k3.dat`: 3-SAT problem resulting from a mapping of the 3-coloring problem `vc-intractable-random-graph.dat`
 - `data/3sat-intractable-random-graph-k4.dat`: 3-SAT problem resulting from a mapping of the 4-coloring problem `vc-intractable-random-graph.dat`
 - `data/3sat-shc-k3.dat`: 3-SAT problem resulting from a mapping of the 3-coloring problem `vc-shc.dat`
 - `data/3sat-shc-k4.dat`: 3-SAT problem resulting from a mapping of the 4-coloring problem `vc-shc.dat`
 - `data/vc-ejyohannan-hard-3sat-k3.dat`: Vertex Coloring problem (with chromatic number 3) resulting from a mapping of the 3-SAT problem `3sat-ejyohannan-hard-3sat.dat`
 - `data/vc-ejyohannan-hard-3sat-k4.dat`: Vertex Coloring problem (with chromatic number 4) resulting from a mapping of the 3-SAT problem `3sat-ejyohannan-hard-3sat.dat`
 - `data/vc-ejyohannan-intractable-3sat-k3.dat`: Vertex Coloring problem (with chromatic number 3) resulting from a mapping of the 3-SAT problem `3sat-ejyohannan-intractable-3sat.dat`
 - `data/vc-hc.dat`: The smallest hard-to-color (HC) graph for the DSatur heuristic of the Vertex Coloring problem
 - `data/vc-intractable-random-graph.dat`: An intractable problem for my implementation of the brute-force solution of the Vertex Coloring problem
 - `data/vc-intractable-connected-graph.dat`: An intractable completely connected graph for my implementation of the brute-force solution of the Vertex Coloring problem. Note that there is no equivalent 3-SAT problem, as the mapping from Vertex Coloring to 3-SAT for this problem was also intractable
 - `data/vc-shc.dat`: The smallest slightly-hard-to-color (SHC) graph for the DSatur heuristic of the Vertex Coloring problem

## Usage

### Input File Format

All input Vertex Coloring graphs and 3-SAT problems should be located in the `data` directory. The prefixes `3sat-` and `vc-` give whether the input is a Vertex Coloring graph or a 3-SAT problem, respectively.

A Vertex Coloring graph should contain the following lines:
 - An integer $V$ equal to the number of vertices in the graph
 - $2E$ lines containing three integers $v_1$, $v_2$, and $w$, separated by spaces, where $E$ is the number of edges in the graph, $v_1$ and $v_2$ are the vertices that are connected, and $w$ is the weight of the edge (irrelevant for the Vertex Coloring problem). Vertices are indexed $1$ to $V$, inclusive. Note that the Vertex Coloring problem assumes an undirected graph, so for all $(v_1, v_2)$ listed, $(v_2, v_1)$ should also be listed.
 - A `$` to mark the end of the input. Any text past the `$` is an annotation.

A 3-SAT problem should contain the following lines:
 - An integer $N$ equal to the number of boolean variables
 - $C$ lines containing containing three integers $x_1$, $x_2$, and $x_3$, separated by spaces, where $C$ is the number of clauses, and $x_1$, $x_2$, and $x_3$ are the three boolean variables in the clause. Boolean variables are indexed $1$ to $N$, inclusive. An $x_i < 0$ corresponds to the negation of boolean variable $|x_i|$.
 - A `$` to mark the end of the input. Any text past the `$` is an annotation.

### Compiling

All C++ scripts can be compliled by running the `make` command in the terminal. Executables can be removed by running the `make clean` command in the terminal.

### Using the Brute-force and Heuristic Algorithms

Typing `./vertex-coloring.exe filename` in the terminal opens the interface for the brute-force and heuristic algorithms on an input file. The terminal will prompt the user for which algorithm to run. After running, the script will annotate the file with its solution.

### Performing the Mappings

To run the Vertex Coloring to 3-SAT mapping on an input file, type `./vc-to-3sat.exe filename` in the terminal. The terminal will prompt the user for what $k$ value to map with (the 3-SAT problem will be satisfiable iff the graph has a $k$-coloring). After running, the script will write the output of the mapping to a file (specified in the terminal).

To run the 3-SAT to Vertex Coloring mapping on an input file, type `./3sat-to-vc.exe filename` in the terminal. The terminal will prompt the user for what $k$ to map with (the graph will have a $k$-coloring iff the 3-SAT problem is satisfiable). After running, the script will write the output of the mapping to a file (specified in the terminal).
