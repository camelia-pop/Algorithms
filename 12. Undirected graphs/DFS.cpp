#include "DFS.h"
#include <stack>

using std::stack;

DFS::DFS(const Graph &G, size_t source, bool rec): 
      marked(vector<bool>(G.numV(), false)),
	  edgeTo(vector<size_t>(G.numV(), G.numV())),
	  s(source) {
	if (rec)
		DFS_recursive(G, s);
	else
		DFS_non_recursive(G, s);
}

void DFS::DFS_recursive(const Graph &G, size_t v) {
	marked[v] = true;	  
	for(size_t u : G.adjV(v))
		if (!marked[u]) {
			DFS_recursive(G, u);
			edgeTo[u] = v;
		}
}

size_t DFS::nextToVisit(const Graph &G, size_t v) const {
	for (size_t u : G.adjV(v))
		if (!marked[u])
			return u;
	return G.numV();	
}

void DFS::DFS_non_recursive(const Graph &G, size_t v) {
	stack<size_t> st;
	size_t u;
	st.push(v);
	marked[v] = true;
	while (!st.empty()) {
		v = st.top();
		u = nextToVisit(G, v);
		if (u != G.numV()) {
			marked[u] = true;
			edgeTo[u] = v;
			st.push(u);
		} else
			st.pop();
	}
}


list<size_t> DFS::pathTo(size_t v) const {
	list<size_t> ls;
	if (hasPathTo(v)) {
		for (size_t u = v; u != s; u = edgeTo[u])
			ls.push_front(u);
		ls.push_front(s);
	}
	return ls;
}

