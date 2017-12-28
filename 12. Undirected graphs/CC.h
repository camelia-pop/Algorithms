#ifndef CONNECTED_COMPONENTS_H
#define CONNECTED_COMPONENTS_H

#include "Graph.h"

class CC {
	public:
		CC(const Graph &);
		size_t numCC() const { return count; };
		size_t idCC(size_t v) const { return id[v]; };
	private:
		void dfs(const Graph &, size_t, vector<bool> &);
	
		size_t count;
		vector<size_t> id;
};

#endif