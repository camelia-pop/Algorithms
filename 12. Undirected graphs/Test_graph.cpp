#include "Graph.h"
#include "BFS.h"
#include "DFS.h"
#include "CC.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::ifstream;

int main() {
	Graph G1(5);
	cout << "Graph G1 (no edges):" << endl;
	print(cout, G1) << endl << endl;
		
	ifstream is("Graph.txt");
	Graph G2(is);
	is.close();
	
	cout << "Graph G2 (input from text file): " << endl;
	print(cout, G2) << endl << endl;
		
	vector<size_t> vec_adj(G2.adjV(0));
	cout << "Vertices adjacent to 0 in graph G2: ";
	for (size_t v : vec_adj)
		cout << v << " ";
	cout << endl << endl;
	
	
	DFS dfs(G2, 0, false);
	cout << "G2 has a path from 0 to 3? " << dfs.hasPathTo(3) << endl << endl;	
	
	cout << "A path in G2 from 0 to 3: ";
	list<size_t> ls(dfs.pathTo(3));
	for (auto it = ls.begin(); it != ls.end(); ++it)
		cout << *it << " ";
	cout << endl << endl;
	
	CC connectedComp(G2);
	cout << "Number of connected components in G2: " 
	     << connectedComp.numCC() << endl << endl;
	cout << "Identifier for each connected component: " << endl;
	for (size_t v = 0; v != G2.numV(); ++v)
		cout << "\t Vertex " << v << ": " 
	         << connectedComp.idCC(v) << endl;
	cout << endl;	
	
	cout << "G2 has a cycle? " << G2.hasCycle() << endl << endl;
		
	is.open("Acyclic_graph.txt");
	Graph G3(is);
	is.close();
	
	cout << "\nGraph G3 (connected and acyclic): " << endl;
	print(cout, G3) << endl;
	cout << "G3 has a cycle? " << G3.hasCycle() << endl << endl;
	
	list<size_t> lsDiameter(G3.diameter());
	cout << "A longest path in the graph G3: ";
	for (auto it = lsDiameter.begin(); it != lsDiameter.end(); ++it)
		cout << *it << " ";
	cout << endl << endl;
	
	cout << "A center in G3: " << G3.center() << endl << endl;
	
	is.open("Euler_graph.txt");
	Graph G4(is);
	is.close();
	
	cout << "\nGraph G4 (connected and Euler): " << endl;
	print(cout, G4) << endl;
	cout << "G4 contains an Euler cycle? " << G4.isEuler() << endl << endl;
	list<size_t> lsEuler(G4.EulerCycle());
	cout << "An Euler cycle in G4: ";
	for (auto it = lsEuler.begin(); it != lsEuler.end(); ++it)
		cout << *it << " ";
	cout << endl << endl;
	
	is.open("Bipartite_graph.txt");
	Graph G5(is);
	is.close();
	cout << "\n\nGraph G5 (bipartite): " << endl;
	print(cout, G5) << endl;
	cout << "Graph G5 bipartite? " << G5.bipartite() << endl<< endl;
}