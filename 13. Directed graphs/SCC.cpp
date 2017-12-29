#include "SCC.h"
#include "TopologicalSort.h"
#include <stack>

using std::stack;

SCC::SCC(const Digraph &G): 
	count(0), id(vector<size_t>(G.numV())), 
	marked(vector<bool>(G.numV(), false)), kerDAG(Digraph(0)) {
	Digraph Grev(G.numV());
	Grev = G.reverse();
	
	TopologicalSort ts(Grev);
	stack<size_t> reversedPostOrder(ts.reversedPostOrder());
	
	while (!reversedPostOrder.empty()) {
		size_t v(reversedPostOrder.top());
		if (!marked[v]) {
			dfs(G, v);
			++count;
		}
		reversedPostOrder.pop();
	}
	
	// create the kernel DAG
	kerDAG = Digraph(count);
	for (size_t v = 0; v != G.numV(); ++v) 
		for (size_t u : G.adjV(v))
			if ((id[u] != id[v]) && (!kerDAG.existsEdge(id[v], id[u])))
				kerDAG.addEdge(id[v], id[u]);
}

vector<size_t> SCC::reachableVertex() const {
	size_t k(kerDAG.reachableVertexDAG());
	vector<size_t> rv;
	if (k != count)
		for (size_t v = 0; v != id.size(); ++v)
			if (id[v] == k)
				rv.push_back(v);
	return rv;		
}

bool SCC::hasReachableVertex() const {
	return kerDAG.reachableVertexDAG() != count;
}

void SCC::dfs(const Digraph &G, size_t v) {
	id[v] = count;
	marked[v] = true;
	for (size_t u : G.adjV(v))
		if (!marked[u]) 
			dfs(G, u);
}
