#include "SP.h"
#include <limits>
#include <stack>

using std::numeric_limits;
using std::stack;

SP::SP(const EdgeWeightedDigraph &G, int s):
	source(s),
	pqv(G.numV()),  
	distTo(G.numV(), numeric_limits<double>::max()), 
	edgeTo(G.numV(), DirectedEdge(0, 0, 0.0)) {
	distTo[s] = 0.0;
	pqv.insert(s, 0.0);
	while (!pqv.isEmpty()) {
		int v = pqv.removeTop();
		for (DirectedEdge e : G.outgoingEdges(v))
			relaxEdge(G, e);
	}
}

void SP::relaxEdge(const EdgeWeightedDigraph &G, const DirectedEdge &e) {
	int v = e.from(), u = e.to();
	if (distTo[u] > distTo[v] + e.weight()) {
		distTo[u] = distTo[v] + e.weight();
		edgeTo[u] = e;
		if (pqv.contains(u))
			pqv.changeKey(u, distTo[u]);
		else
			pqv.insert(u, distTo[u]);
	}
} 

vector<DirectedEdge> SP::pathTo(int v) const {
	if ((!hasPathTo(v)) || (v == source))
		return vector<DirectedEdge>();
	stack<DirectedEdge> st;
	do {
		st.push(edgeTo[v]);
		v = edgeTo[v].from();	
	} while (v != source);
	vector<DirectedEdge> links;
	while (!st.empty()) {
		links.push_back(st.top());
		st.pop();
	}
	return links;
}