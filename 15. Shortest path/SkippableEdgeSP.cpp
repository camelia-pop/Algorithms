/*
3. Shortest path with one skippable edge. 

Given an edge-weighted digraph, design an Elog(V) algorithm to find a shortest path from s to t where you can change the weight of any one edge to zero. Assume the edge weights are nonnegative.

Solution:
Find the shortest paths from s to all vertices of the graph. distToS, edgeToS O(ElogV)

Reverse the edges of the graph and find the shortest paths from t to all vertices of the graph. distToT, edgeToS O(ElogV)

For all vertices of the graph v, look at all edges emerging from v, v-w. Minimize distToS[v] + distoToT[w] (set weight(v-w) = 0).
*/

#include "SP.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::numeric_limits;
using std::reverse;
using std::vector;

int main() {
	ifstream is("SkippableEdge.txt");
	EdgeWeightedDigraph G(is);
	is.close();
	cout << "Graph: " << endl;
	print(cout, G) << endl << endl;
	
	int s = 0, t = 2;
	SP startSP(G, s);

	if (!startSP.hasPathTo(t)) {
		cout << "There is no path from " << s << " to " << t << endl;
		return 0;
	} else {
		cout << "Shortest path from " << s << " to " << t << ": " << endl;
		vector<DirectedEdge> sp = startSP.pathTo(t);
		for (DirectedEdge e : sp)
			cout << e.to_string() << endl;
		cout << endl << endl;	
	}
	
	SP endSP(G.reverse(), t);
	int v, u;
	double L = numeric_limits<double>::max(), currL;
	vector<DirectedEdge> path, vec;
	DirectedEdge skippableEdge(0, 0, 0.0);
		
	for (DirectedEdge e : G.edges()) {
		v = e.from();
		u = e.to();
		currL = startSP.distanceTo(v) + endSP.distanceTo(u);
		if (L > currL) {
			L = currL;
			skippableEdge = e;
			path = startSP.pathTo(v);
			path.push_back(DirectedEdge(v, u, 0.0));
			vec = endSP.pathTo(u);
			reverse(vec.begin(), vec.end());
			for (DirectedEdge eloc : vec)
				path.push_back(DirectedEdge(eloc.to(), eloc.from(), eloc.weight()));
		}
	}

	cout << "Skippable edge: " << skippableEdge.to_string() << endl << endl;
	cout << "Shortest path from " << s << " to " << t << " with skippable edge: " << endl;
	for (DirectedEdge e : path)
		cout << e.to_string() << endl;
	cout << endl << endl;	
}