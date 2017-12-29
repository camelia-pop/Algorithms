#include "Digraph.h"
#include "DirectedCycle.h"
#include "HamiltonianPath.h"
#include "SCC.h"
#include "TopologicalSort.h"

Digraph::Digraph(ifstream &is): E(0) {
	is >> V;
	for (size_t i = 0; i != V; ++i)
		adj.push_back(vector<size_t>());
	size_t u, v;
	while (is >> u >> v) {
		adj[u].push_back(v);
		++E;
	}
}

Digraph Digraph::reverse() const {
	Digraph Grev(V);
	for (size_t v = 0; v != V; ++v)
		for (size_t u : adjV(v))
			Grev.addEdge(u, v);
	return Grev;	
}

bool Digraph::existsEdge(size_t v, size_t u) const {
	for (size_t w : adjV(v))
		if (w == u)
			return true;
	return false;
}

// we can implement this using any cycle not necessarily the shortest one
bool Digraph::isDAG() const { 
	return !DirectedCycle(*this).hasCycle(); 
};

stack<size_t> Digraph::reversedPostOrder() const {
	return TopologicalSort(*this).reversedPostOrder();
}

// this member function requires G to be DAG
bool Digraph::hasHamiltonianPath() const {
	return HamiltonianPath(*this).hasHamiltonianPath();
}

// this member function requires G to be DAG
stack<size_t> Digraph::HamPath() const {
	return HamiltonianPath(*this).HamPath();
}

// this member function requires G to be DAG
size_t Digraph::reachableVertexDAG() const {
	vector<bool> marked(V, false);
	size_t rv; // variable in which we keep the reachable vertex
	// rv = V means we found no reachable vertex from all vertices of the DAG;
	rv = dfsOnePath(0, marked);
	for (size_t v = 1; v != V; ++v) 
		if (!marked[v]) {
			size_t u(dfsOnePath(v, marked));
			if ((u != V) && (u != rv))
				return V;
		}
	return rv;
}

// helper functions for size_t reachableVertex()
// nextToVisit returns V if all the vertices in adj[v] were visited before or if adj[v] is empty 
size_t Digraph::nextToVisit(size_t v, const vector<bool> &marked) const {
	for (size_t u : adjV(v))
		if (!marked[u])
			return u;
	return V;	
}

size_t Digraph::dfsOnePath(size_t v, vector<bool> &marked) const {
	while (v != V) {
		marked[v] = true;
		if (adj[v].empty())
			return v;
		v = nextToVisit(v, marked);
	}
	return v;
}