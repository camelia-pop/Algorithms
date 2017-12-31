#ifndef EDGE_WEIGHTED_GRAPH
#define EDGE_WEIGHTED_GRAPH

#include "Edge.h"
#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using std::vector;

class EdgeWeightedGraph;

ostream &print(ostream &, const EdgeWeightedGraph &);

class EdgeWeightedGraph {
	public:
		EdgeWeightedGraph(int VV): V(VV), E(0),
				adj(vector<vector<Edge>>(VV, vector<Edge>())) {};
		EdgeWeightedGraph(ifstream &);
		int numV() const { return V; };
		int numE() const { return E; };
		vector<Edge> adjE(int v) const { return adj[v]; };
		vector<Edge> edges() const;
		void addEdge(const Edge &e) {
			int v = e.either();
			adj[v].push_back(e);
			adj[e.other(v)].push_back(e);
			++E;	
		};
		bool contains(const Edge &) const;
		bool isInMST(const Edge &) const;	
	private:
		int V, E;
		vector<vector<Edge>> adj;	
};

#endif