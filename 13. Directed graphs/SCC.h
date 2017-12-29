#ifndef STRONG_CONNECTED_COMPONENTS_H
#define STRONG_CONNECTED_COMPONENTS_H

#include "Digraph.h"

class SCC {
	public:
		SCC(const Digraph &);
		vector<size_t> reachableVertex() const;
		bool hasReachableVertex() const;
	private:
		void dfs(const Digraph &, size_t);
		
		size_t count; // number of strongly connected components
		vector<size_t> id; // id[v] = number of the SCC of the vertex v
		vector<bool> marked;
		Digraph kerDAG;	
};

#endif