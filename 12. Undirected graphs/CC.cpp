#include "CC.h"

CC::CC(const Graph &G): count(0), id(vector<size_t>(G.numV())) {
	vector<bool> marked(G.numV(), false);
	for (size_t v = 0; v != G.numV(); ++v)
		if (!marked[v]) {
			dfs(G, v, marked);
			++count;
		}
}

// helper functions
void CC::dfs(const Graph &G, size_t v, vector<bool> &marked) {
	marked[v] = true;
	id[v] = count;
	for (size_t u : G.adjV(v))
		if (!marked[u])
			dfs(G, u, marked);
}