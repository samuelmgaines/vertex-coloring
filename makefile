all:
	g++ vertex-coloring.cpp read-graph.cpp brute-force.cpp heuristic.cpp -o vertex-coloring.exe
	g++ vc-to-3sat.cpp read-graph.cpp -o vc-to-3sat.exe
	g++ 3sat-to-vc.cpp read-sat.cpp -o 3sat-to-vc.exe
clean:
	rm vertex-coloring.exe vc-to-3sat.exe 3sat-to-vc.exe