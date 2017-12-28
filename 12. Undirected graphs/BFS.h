#ifndef BFS_H
#define BFS_H

#include "Graph.h"

class BFS {
	public:
		BFS(const Graph &, size_t);
		size_t aFarthestVertex() const;
		bool hasPathTo(size_t v) const { return marked[v]; };
		list<size_t> pathTo(size_t) const;
	private:
		vector<bool> marked;
		vector<size_t> edgeTo;
		vector<size_t> distanceTo;
		size_t s;
};

#endif