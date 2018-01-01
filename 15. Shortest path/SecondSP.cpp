/*
2. Second shortest path. 

Given an edge-weighted digraph and let P be a shortest path from vertex s to vertex t. Design an Elog(V) algorithm to find a path other than P from s to t that is as short as possible. Assume all of the edge weights are strictly positive.

Solution:
Find the shortest paths from s to all vertices of the graph. distToS O(ElogV)

Reverse the edges of the graph and find the shortest paths from t to all vertices of the graph. distToT O(ElogV)

Find a vertex v such that it minimizes distToS[v] + distToT[v] under the constraint distToS[v] + distToT[v] >= shortest path s-t, and s-v union v-t is not the shortest path. O(V)
*/

#include "SP.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::numeric_limits;
using std::reverse;
using std::vector;

int main() {
	ifstream is("EdgeWeightedDigraph2.txt");
	EdgeWeightedDigraph G(is);
	is.close();
	cout << "Graph: " << endl;
	print(cout, G) << endl << endl;
	
	int s = 0, t = 6;
	SP startSP(G, s);
	vector<DirectedEdge> sp;
	
	if (!startSP.hasPathTo(t)) {
		cout << "There is no path from " << s << " to " << t << endl;
		return 0;
	} else {
		cout << "Shortest path from " << s << " to " << t << ": " << endl;
		sp = startSP.pathTo(t);
		for (DirectedEdge e : sp)
			cout << e.to_string() << endl;
		cout << endl << endl;
	}
	
	SP endSP(G.reverse(), t);	
	double L0 = startSP.distanceTo(t), L = numeric_limits<double>::max(), currL;
	double eps = 1e-7; // for numerical errors with doubles
	int v0 = -1;
	vector<DirectedEdge> secondSP, vec;
	
	for (size_t v = 0; v != G.numV(); ++v) {
		currL = startSP.distanceTo(v) + endSP.distanceTo(v);
		if (currL - L0 < eps) {
			secondSP = startSP.pathTo(v);
			vec = endSP.pathTo(v);
			reverse(vec.begin(), vec.end());
			for (DirectedEdge e : vec)
				secondSP.push_back(DirectedEdge(e.to(), e.from(), e.weight()));
			if (secondSP != sp) {
				cout << "A second shortest path from " << s << " to " << t << ": " << endl;
				for (DirectedEdge e : secondSP)
					cout << e.to_string() << endl;
				cout << endl << endl;
				return 0;
			}
		} else 		
			if (L > currL) {
				L = currL;
				v0 = v; 
			}
	}
	
	if (v0 == -1)
		cout << "There is no second shortest shortest path" << endl;
	else {
		secondSP = startSP.pathTo(v0);
		vec = endSP.pathTo(v0);
		reverse(vec.begin(), vec.end());
		for (DirectedEdge e : vec)
			secondSP.push_back(DirectedEdge(e.to(), e.from(), e.weight()));
		cout << "A second shortest path from " << s << " to " << t << ": " << endl;
		for (DirectedEdge e : secondSP)
			cout << e.to_string() << endl;
		cout << endl << endl;
	}	
}