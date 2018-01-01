#ifndef EDGE_WEIGHTED_DIGRAPH_H
#define EDGE_WEIGHTED_DiGRAPH_H

#include "DirectedEdge.h"
#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::vector;

class EdgeWeightedDigraph;

ostream &print(ostream &, const EdgeWeightedDigraph &);

class EdgeWeightedDigraph {
	public:
		EdgeWeightedDigraph(int VV): V(VV), E(0),
				adj(vector<vector<DirectedEdge>>(VV, vector<DirectedEdge>())) {};
		EdgeWeightedDigraph(ifstream &);
		EdgeWeightedDigraph reverse() const;
		void addDirectedEdge(const DirectedEdge &e) {
			int v = e.from();
			adj[v].push_back(e);
			++E;	
		};
		int numV() const { return V; };
		int numE() const { return E; };
		vector<DirectedEdge> edges() const;
		vector<DirectedEdge> outgoingEdges(int v) const { return adj[v]; };
		vector<DirectedEdge> incomingEdges(int) const;	
	private:
		int V, E;
		vector<vector<DirectedEdge>> adj;	
};

#endif