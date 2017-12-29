#include "ShortestDirectedCycle.h"
#include <algorithm>
#include <stack>

using std::reverse;
using std::stack;

ShortestDirectedCycle::ShortestDirectedCycle(const Digraph &G):
	cycle(vector<size_t>()) {
	vector<size_t> new_cycle;
	for (size_t v = 0; v != G.numV(); ++v) {
		new_cycle = dfs(G, v);
		if (new_cycle.size())
			if ((cycle.size() == 0) || (cycle.size() > new_cycle.size()))
				cycle = new_cycle;
	}
}

size_t ShortestDirectedCycle::nextToVisit
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

size_t ShortestDirectedCycle::nextToVisit
      (const Digraph &G, size_t v, const vector<bool> &marked) const {
	for (size_t u : G.adjV(v))
		if (!marked[u])
			return u;
	return G.numV();	
}


vector<size_t> ShortestDirectedCycle::dfs(const Digraph &G, size_t v) const {
	vector<size_t> sdc;
	vector<bool> marked(G.numV(), false), onStack(G.numV(), false);
	stack<size_t> st;
	
	size_t u;
	st.push(v);
	marked[v] = true;
	onStack[v] = true;
	while (!st.empty()) {
		v = st.top();
		u = nextToVisit(G, v, marked, onStack);
		if ((u != G.numV()) && onStack[u]) {
			// create a new cycle
			vector<size_t> sdc_new;
			stack<size_t> st_new(st);
			sdc_new.push_back(0);
			sdc_new.push_back(u);
			while (!G.existsEdge(u, st_new.top())) {
				sdc_new.push_back(st_new.top());
				st_new.pop();		
			}
			sdc_new[0] = st_new.top();
			sdc_new.push_back(st_new.top());
			reverse(sdc_new.begin(), sdc_new.end());
			if ((sdc.size() == 0) || (sdc.size() > sdc_new.size()))
				sdc = sdc_new;
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
	return sdc;
}
