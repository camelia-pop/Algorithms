#include "DirectedCycle.h"
#include <algorithm>
#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::reverse;
using std::stack;

DirectedCycle::DirectedCycle(const Digraph &G):
	cycle(vector<size_t>()) {
	for (size_t v = 0; v != G.numV(); ++v) {
		cycle = dfs(G, v);
		if (cycle.size())
			break;
	}
}

size_t DirectedCycle::nextToVisit
    (const Digraph &G, size_t v, const vector<bool> &marked, 
	const vector<bool> &onStack) const {
	for (size_t u : G.adjV(v))
		if (onStack[u])
			return u;
		else
			if (!marked[u])
				return u;
	return G.numV();	
}

size_t DirectedCycle::nextToVisit
    (const Digraph &G, size_t v, const vector<bool> &marked) const {
	for (size_t u : G.adjV(v))
		if (!marked[u])
			return u;
	return G.numV();	
}

vector<size_t> DirectedCycle::dfs(const Digraph &G, size_t v) {
	vector<bool> marked(G.numV(), false), onStack(G.numV(), false);
	stack<size_t> st;
	
	st.push(v);
	marked[v] = true;
	onStack[v] = true;
	while (!st.empty()) {
		v = st.top();
		size_t u = nextToVisit(G, v, marked, onStack);
		if ((u != G.numV()) && onStack[u]) {
			// create a cycle to be returned
			cycle.push_back(0);
			cycle.push_back(u);
			while (!G.existsEdge(u, st.top())) {
				cycle.push_back(st.top());
				st.pop();		
			}
			cycle[0] = st.top();
			cycle.push_back(st.top());
			reverse(cycle.begin(), cycle.end());
			return cycle;
		}
		u = nextToVisit(G, v, marked);
		if (u != G.numV()) {
			marked[u] = true;
			onStack[u] = true;
			st.push(u);
		} else {
			onStack[v] = false;
			st.pop();
		}
	}
	return cycle;
}

