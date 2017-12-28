#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::find;
using std::ifstream;
using std::list;
using std::ostream;
using std::size_t;
using std::vector;

class Graph;

ostream &print(ostream &, const Graph &);

class Graph {
	friend ostream &print(ostream &, const Graph &);
	public:
		Graph(int v): V(v), E(0),
				adj(vector<vector<size_t>>(v, vector<size_t>())) {};
		Graph(ifstream &);
		void addEdge(size_t u, size_t v) { 
			adj[u].push_back(v);
			adj[v].push_back(u);
			++E;	
		};
		// adjacent edges to vertex v
		vector<size_t> adjV(size_t v) const { return adj[v]; };
		// number of vertices
		size_t numV() const { return V; };
		// number of edges
		size_t numE() const { return E; };
		bool edgeExists(size_t v, size_t u) const {
			return 
			(find(adj[v].begin(), adj[v].end(), u) != adj[v].end());
		};
		size_t degree(size_t v) const { return adj[v].size(); };
		// check if a graph is Euler
		bool isEuler() const;
		// return an Euler cycle
		list<size_t> EulerCycle() const;
		// check if a graph is bipartite
		bool bipartite() const;
		// check if a graph has a cycle
		bool hasCycle() const;
		// diameter() and center() assume the graph is not cyclic
		// find a longest simple path
		list<size_t> diameter() const;
		// find the middle vertex in a longest simple path
		size_t center() const;
	private:
		size_t nextToVisit(size_t, const vector<bool> &) const;
	
		size_t V;
		size_t E;
		vector<vector<size_t>> adj;
};

#endif