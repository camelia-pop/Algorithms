#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

EdgeWeightedDigraph::EdgeWeightedDigraph(ifstream &is) {
	is >> V;
	for (size_t i = 0; i != V; ++i)
		adj.push_back(vector<DirectedEdge>());
	int vv, uu;
	double ww;
	while (is >> vv >> uu >> ww) {
		adj[vv].push_back(DirectedEdge(vv, uu, ww));
		++E;
	}
}

EdgeWeightedDigraph EdgeWeightedDigraph::reverse() const {
	EdgeWeightedDigraph Grev(V);
	for (size_t v = 0; v != V; ++v)
		for (DirectedEdge e : adj[v])
			Grev.addDirectedEdge(DirectedEdge(e.to(), e.from(), e.weight()));
	return Grev;
}

vector<DirectedEdge> EdgeWeightedDigraph::edges() const {
	vector<DirectedEdge> links;
	for (size_t i = 0; i != V; ++i) 
		for (DirectedEdge e : adj[i])
			links.push_back(e);				
	return links;
}

vector<DirectedEdge> EdgeWeightedDigraph::incomingEdges(int v) const {
	vector<DirectedEdge> links;
	for (size_t i = 0; i != V; ++i) 
		for (DirectedEdge e : adj[i])
			if (e.to() == v)
				links.push_back(e);				
	return links;
}

// friend functions
ostream &print(ostream &os, const EdgeWeightedDigraph &G) {
	os << G.numV() << endl << G.numE() << endl;
	vector<DirectedEdge> links(G.edges());
	for (size_t i = 0; i != links.size(); ++i)
		os << links[i].to_string() << endl;
	return os;
}