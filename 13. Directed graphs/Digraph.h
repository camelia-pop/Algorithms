#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::find;
using std::ifstream;
using std::size_t;
using std::stack;
using std::vector;

class Digraph {
	public:
		Digraph(int v): V(v), E(0),
				adj(vector<vector<size_t>>(v, vector<size_t>())) {};
		Digraph(ifstream &);
		void addEdge(size_t u, size_t v) { 
			adj[u].push_back(v);
			++E;	
		};
		vector<size_t> adjV(size_t v) const { return adj[v]; };
		Digraph reverse() const;
		bool existsEdge(size_t, size_t) const;
		size_t numV() const { return V; };
		size_t numE() const { return E; };
		bool isDAG() const;		
		stack<size_t> reversedPostOrder() const;
		// the next four member functions requires G to be DAG
		bool hasHamiltonianPath() const;
		stack<size_t> HamPath() const;	
		size_t reachableVertexDAG() const;
		bool hasReachableVertexDAG() const 
			{ return reachableVertexDAG() != V;};
	private:
		size_t nextToVisit(size_t, const vector<bool> &) const;
		size_t dfsOnePath(size_t, vector<bool> &) const;
			
		size_t V;
		size_t E;
		vector<vector<size_t>> adj;
};

#endif