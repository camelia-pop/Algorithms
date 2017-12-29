#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include "Digraph.h"
#include <stack>
#include <vector>

using std::size_t;
using std::stack;
using std::vector;

class TopologicalSort {
	public:
		TopologicalSort(const Digraph &);
		stack<size_t> reversedPostOrder() const 
			{ return revPostOrder; };		
	private:
		void dfs(const Digraph &, size_t);
		vector<bool> marked;
		stack<size_t> revPostOrder;
};

#endif
