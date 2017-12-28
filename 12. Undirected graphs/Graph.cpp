#include "Graph.h"
#include "BFS.h"
#include <queue>
#include <stack>

using std::queue;
using std::stack;

Graph::Graph(ifstream &is): E(0) {
	is >> V;
	for (size_t i = 0; i != V; ++i)
		adj.push_back(vector<size_t>());
	size_t u, v;
	while (is >> u >> v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
		++E;
	}
}

// use breath first search to traverse the graph and assign colors. The vertices with even distance to the source will have color 0 and the vertices with odd distance to the root will have color 1. There should be no contradiction in assigning colors in order for the graph to be bipartitte.
bool Graph::bipartite() const {
	vector<bool> marked(V, false);	  
	vector<size_t> color(V, 2); // 2 = no color assigned
	for (size_t v = 0; v != V; ++v) {
		if (!marked[v]) {
			color[v] = 0;
			marked[v] = true;
			queue<size_t> q;
			q.push(v);
			while (!q.empty()) {
				size_t u(q.front());
				q.pop();
				for (size_t w : adj[u]) {
					if (color[w] == color[u])
						return false;
					if (!marked[w]) {
						q.push(w);
						marked[w] = true;
						color[w] = (color[u] + 1) % 2;
					}
				}
			}
		}
	}
	return true;
}

// returns a vertex connected to v through an edge. If no such vertex exists, returns V.
size_t Graph::nextToVisit(size_t v, const vector<bool> &marked) const {
	for (size_t u : adj[v])
		if (!marked[u])
			return u;
	return V;	
}

// use depth first search. For each new vertex check if is connected to marked nodes different than the vertex that has just been visited.
// does not work for self loops
bool Graph::hasCycle() const {
	vector<bool> marked(V, false);	  
	vector<size_t> edgeTo(V);
	for (size_t s = 0; s != V; ++s) {
		stack<size_t> st;
		size_t v(s);
		st.push(v);
		marked[v] = true;
		while (!st.empty()) {
			v = st.top();
			size_t u = nextToVisit(v, marked);
			if (u != V) {
				marked[u] = true;
				edgeTo[u] = v;
				st.push(u);
				for (size_t w : adj[u])
					if (marked[w] && (w != v))
						return true;
			} else
				st.pop();
		}
	}
	return false;
}

list<size_t> Graph::diameter() const {
	BFS bfs1(*this, 0);
	size_t start(bfs1.aFarthestVertex());
	BFS bfs2(*this, start);
	size_t end(bfs2.aFarthestVertex());
	return bfs2.pathTo(end);
}

size_t Graph::center() const {
	list<size_t> lsd(diameter());
	size_t n(lsd.size() / 2);
	list<size_t>::iterator it(lsd.begin());
	for (size_t i = 0; i !=  n; ++i) 
		++it;
	return *it;
}

bool Graph::isEuler() const {
	for (size_t v = 0; v != V; ++v)
		if (degree(v) % 2)
			return false;
	return true;	
}

size_t unmarkedAdj(const vector<bool> &marked, const vector<size_t> &a) {
	for (size_t i = 0; i != a.size(); ++i)
		if (!marked[i])
			return i;
	return a.size();	
}

size_t indexVertex(size_t v, const vector<size_t> &a) {
	for (size_t i = 0; i != a.size(); ++i)
		if (a[i] == v)
			return i;
	return a.size();	
}

list<size_t> Graph::EulerCycle() const {
	list<size_t> ls;
	if (!isEuler()) 
		return ls;
	
	vector<vector<bool>> marked;
	for (size_t v = 0; v != V; ++v)
		marked.push_back(vector<bool>(adj[v].size(), false));
	// find a first cycle;
	size_t s(0);
	size_t v(s), i(unmarkedAdj(marked[s], adj[s])), u;
	while (i != adj[v].size()) {
		ls.push_back(v);
		u = adj[v][i];
		marked[v][i] = true;
		size_t j(indexVertex(v, adj[u]));
		marked[u][j] = true;
		v = u;	
		i = unmarkedAdj(marked[v], adj[v]);
	}
	ls.push_back(v);
	// search for a new starting point for a cycle
	list<size_t>::iterator it = ls.begin();
	while (it != ls.end() 
		   && (unmarkedAdj(marked[*it], adj[*it]) == adj[*it].size()))
		++it;
	// find the remaining cycles
	while (it != ls.end()) {
		s = *it;
		v = s;
		i = unmarkedAdj(marked[s], adj[s]);		
		// search for an unseen cycle starting at s
		list<int> cycle;
		while (i != adj[v].size()) {
			cycle.push_back(v);
			u = adj[v][i];
			marked[v][i] = true;
			size_t j(indexVertex(v, adj[u]));
			marked[u][j] = true;
			v = u;	
			i = unmarkedAdj(marked[v], adj[v]);
		}
		// insert the new cycle into the list
		ls.insert(it, cycle.begin(), cycle.end());
		// search for a new starting point for a cycle
		it = ls.begin();
		while (it != ls.end() 
			  && (unmarkedAdj(marked[*it], adj[*it]) == adj[*it].size()))
		    ++it;
	}
	return ls;
}

// friend functions
ostream &print(ostream &os, const Graph &G) {
	os << "Number of vertices: " << G.numV() << endl;
	os << "Number of edges: " << G.numE() << endl;
	if (G.numE())
		os << "Adjacency list for each vertex:" << endl;
	for (size_t i = 0; i != G.adj.size(); ++i) 
		if (G.adj[i].size()){
			os << "\t Vertex " << i << ": ";
			for (size_t j : G.adj[i])
				os << j << " ";
			os << endl;
	}
	return os;
}