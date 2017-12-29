#ifndef DIRECTED_CYCLE
#define DIRECTED_CYCLE

#include "Digraph.h"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

class DirectedCycle {
	public:
		DirectedCycle(const Digraph &);
		bool hasCycle() const { return (!cycle.empty()); };
		vector<size_t> directedCycle() const { return cycle; };
	private:
		// helper functions
		vector<size_t> dfs(const Digraph &, size_t);
		size_t nextToVisit(const Digraph &, size_t, 
		       const vector<bool> &, const vector<bool> &) const;
		size_t nextToVisit(const Digraph &, size_t, 
		       const vector<bool> &) const;

		vector<size_t> cycle;
};

#endif