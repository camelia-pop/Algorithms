#ifndef MINIMUM_SPANNING_TREE_H
#define MINIMUM_SPANNING_TREE_H

#include "Edge.h"
#include "EdgeWeightedGraph.h"
#include "IndexPQ.h"
#include <algorithm>
#include <functional>
#include <limits>
#include <vector>

using std::less;
using std::numeric_limits;
using std::sort;
using std::vector;

// Eager Prim implementation

template <typename Comparator = less<double>>
class MST {
	public:
		MST(const EdgeWeightedGraph &);
		vector<Edge> edges() const;
		double weight() const;
	private:
		void visit(const EdgeWeightedGraph &, int);
		
		IndexPQ<double, Comparator> pqv;
		vector<double> distTo;
		vector<Edge> edgeTo;
		vector<bool> marked;
};

template <typename Comparator>
MST<Comparator>::MST(const EdgeWeightedGraph &G): 
	pqv(G.numV(), Comparator()), distTo(G.numV(), numeric_limits<double>::max()), 
	edgeTo(G.numV(), Edge(0, 0, 0.0)), marked(G.numV(), false) {
	distTo[0] = 0.0;
	pqv.insert(0, 0.0);
	while (!pqv.isEmpty())
		visit(G, pqv.removeTop());
}

template <typename Comparator>
vector<Edge> MST<Comparator>::edges() const {
	vector<Edge> vecEdges;
	for (int v = 1; v != edgeTo.size(); ++v)
		vecEdges.push_back(edgeTo[v]);
	return vecEdges;
}

template <typename Comparator>
double MST<Comparator>::weight() const {
	double wt;
	for (int v = 1; v != edgeTo.size(); ++v)
		wt += edgeTo[v].weight();
	return wt;
}

// helper functions
template <typename Comparator>
void MST<Comparator>::visit(const EdgeWeightedGraph &G, int v) {
	marked[v] = true;
	for (Edge e : G.adjE(v)) {
		int u = e.other(v);
		if (!marked[u]) 
			if (e.weight() < distTo[u]){
				edgeTo[u] = e;
				distTo[u] = e.weight();
				if (pqv.contains(u))
					pqv.changeKey(u, e.weight());
				else
					pqv.insert(u, e.weight());
			}
	}
}

#endif