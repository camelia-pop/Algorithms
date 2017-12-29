#include "Digraph.h"
#include "TopologicalSort.h"

TopologicalSort::TopologicalSort(const Digraph &G):
	marked(vector<bool>(G.numV(), false)),
	revPostOrder(stack<size_t>()) {
		for (size_t v = 0; v != G.numV(); ++v)
			if (!marked[v])
				dfs(G, v);
}

void TopologicalSort::dfs(const Digraph &G, size_t v) {
	marked[v] = true;
	for (size_t u : G.adjV(v))
		if (!marked[u])
			dfs(G, u);
	revPostOrder.push(v);	
} 