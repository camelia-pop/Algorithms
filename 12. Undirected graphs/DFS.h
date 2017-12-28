#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include "Graph.h"
#include <list>

using std::list;

class DFS {
	public:
		DFS(const Graph &G, size_t source, bool rec = true);
		bool hasPathTo(size_t v) const { return marked[v]; };
		list<size_t> pathTo(size_t) const;
	private:
		// helper functions
		void DFS_recursive(const Graph &, size_t);
		void DFS_non_recursive(const Graph &, size_t);
		size_t nextToVisit(const Graph &, size_t) const;
		
		vector<bool> marked;
		vector<size_t> edgeTo;
		size_t s;
};

#endif