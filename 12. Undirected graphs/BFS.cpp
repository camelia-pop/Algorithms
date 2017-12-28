#include "BFS.h"
#include <queue>

using std::queue;

BFS::BFS(const Graph &G, size_t source):
	  marked(G.numV(), false),
	  edgeTo(G.numV(), G.numV()),
	  distanceTo(G.numV()),
	  s(source) {
	size_t v;	  
	queue<size_t> q;
	q.push(s);
	marked[s] = true;
	distanceTo[s] = 0;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (size_t u : G.adjV(v))
			if (!marked[u]) {
				q.push(u);
				marked[u] = true;
				edgeTo[u] = v;
				distanceTo[u] = 1 + distanceTo[v];
			}
	}
}

size_t BFS::aFarthestVertex() const {
	size_t dmax(0), v(s);
	for (size_t u = 0; u != marked.size(); ++u)
		if ((marked[u]) && (distanceTo[u] > dmax)) {
			dmax = distanceTo[u];
			v = u;
		}
	return v;	
}

list<size_t> BFS::pathTo(size_t v) const {
	list<size_t> ls;
	if (hasPathTo(v)) {
		for (size_t u = v; u != s; u = edgeTo[u])
			ls.push_front(u);
		ls.push_front(s);
	}
	return ls;
}