#include "Edge.h"
#include "EdgeWeightedGraph.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using std::cout;
using std::endl;
using std::find;
using std::queue;
using std::vector;

EdgeWeightedGraph::EdgeWeightedGraph(ifstream &is) {
	is >> V;
	for (size_t i = 0; i != V; ++i)
		adj.push_back(vector<Edge>());
	int vv, uu;
	double ww;
	while (is >> vv >> uu >> ww) {
		adj[vv].push_back(Edge(vv, uu, ww));
		adj[uu].push_back(Edge(vv, uu, ww));
		++E;
	}
}

vector<Edge> EdgeWeightedGraph::edges() const {
	vector<Edge> links;
	for (size_t i = 0; i != V; ++i) 
		for (Edge e : adj[i])
			if (find(links.begin(), links.end(), e) == links.end()) 
				links.push_back(e);				
	return links;
}

bool EdgeWeightedGraph::contains(const Edge &e) const {
	for (size_t i = 0; i != V; ++i) 
		for (Edge enew : adj[i])
			if (enew == e)
				return true;
	return false;
}

bool EdgeWeightedGraph::isInMST(const Edge &e) const {
	if (!contains(e))
		return false;
	queue<int> q;
	vector<int> marked(V, 0);
	int v = e.either(), u = e.other(v), w, z;
	double weight_e = e.weight();
	// BSF from v
	q.push(v);
	// mark with +1 the vertices visited from v;
	marked[v] = 1;
	while (!q.empty()) {
		w = q.front();
		q.pop();
		for (Edge edg : adj[w]) {
			z = edg.other(w);
			if (marked[z] == 0)
				if (edg.weight() < weight_e) {
					marked[z] = 1;
					q.push(z);
				}
		}
	}
	if (marked[u] == 1)
		return false;
	// BFS from u;
	q.push(u);
	// mark with -1 the vertices visited from w
	marked[u] = -1;
	while (!q.empty()) {
		w = q.front();
		q.pop();
		for (Edge edg : adj[w]) {
			z = edg.other(w);
			if (marked[z] == 0) {
				if (edg.weight() < weight_e) {
					marked[z] = -1;
					q.push(z);
				}
			} else
				if (marked[z] == 1) 
					if (edg.weight() < weight_e)
						return false;
		}
	}
	return true;
}

// friend functions
ostream &print(ostream &os, const EdgeWeightedGraph &G) {
	os << G.numV() << endl;
	os << G.numE() << endl;
	vector<Edge> links(G.edges());
	for (size_t i = 0; i != links.size(); ++i)
		os << links[i].to_string() << endl;
	return os;
}