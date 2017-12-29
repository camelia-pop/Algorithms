#include "SAP.h"
#include <algorithm>
#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::queue;
using std::max;

int SAP::length(int v, int w) const {
	return length(vector<int>(1, v), vector<int>(1, w));
}

int SAP::length(vector<int> vv, vector<int> ww) const {
	// check if arguments are valid
	for (int v : vv) 
		if (v >= G.numV())
			return -1;
	for (int w : ww) 
		if (w >= G.numV())
			return -1;		
	// initialization for v
	vector<bool> marked(G.numV(), false);
	queue<int> q;
	for (int v : vv) {
		q.push(v);
		marked[v] = true;		
	}
	vector<int> distTov(G.numV(), 0);
	// BFS from vertices of vv
	int v;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (int u : G.adjV(v)) 
			if (!marked[u]) {
				q.push(u);
				marked[u] = true;
				distTov[u] = 1 + distTov[v];
			}
	}
	for (int u = 0; u != G.numV(); ++u)
		if (!marked[u])
			distTov[u] = G.numV();
		else 
			marked[u] = false; // reuse marked for BSF from w
	// initialization for w
	int dmin = G.numV();
	vector<int> distTow(G.numV(), 0);
	for (int w : ww) {
		q.push(w);
		marked[w] = true;
		if (dmin > max(distTov[w], distTow[w])) {
			dmin = max(distTov[w], distTow[w]);
		}	
	}	
	// BFS from vertices of ww; change distTo to hold the maximum between distTov and distTow and remember a vertex where distTo is minimum
	int w;
	while (!q.empty()) {
		w = q.front();
		q.pop();
		for (int u : G.adjV(w)) 
			if (!marked[u]) {
				q.push(u);
				marked[u] = true;
				distTow[u] = 1 + distTow[w];
				if (dmin > max(distTov[u], distTow[u])) {
					dmin = max(distTov[u], distTow[u]);
				}
			}
	}
	if (dmin != G.numV())
		return dmin;
	else
		return -1;
}

int SAP::ancestor(int v, int w) const {
	return ancestor(vector<int>(1, v), vector<int>(1, w));
}

int SAP::ancestor(vector<int> vv, vector<int> ww) const {
	// check if arguments are valid
	for (int v : vv) 
		if (v >= G.numV())
			return -1;
	for (int w : ww) 
		if (w >= G.numV())
			return -1;		
	// initialization for v
	vector<bool> marked(G.numV(), false);
	queue<int> q;
	for (int v : vv) {
		q.push(v);
		marked[v] = true;		
	}
	vector<int> distTov(G.numV(), 0);
	// BFS from vertices of vv
	int v;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (int u : G.adjV(v)) 
			if (!marked[u]) {
				q.push(u);
				marked[u] = true;
				distTov[u] = 1 + distTov[v];
			}
	}
	for (int u = 0; u != G.numV(); ++u)
		if (!marked[u])
			distTov[u] = G.numV();
		else 
			marked[u] = false; // reuse marked for BSF from w
	// initialization for w
	int dmin = G.numV(), anc;
	vector<int> distTow(G.numV(), 0);
	for (int w : ww) {
		q.push(w);
		marked[w] = true;
		if (dmin > max(distTov[w], distTow[w])) {
			dmin = max(distTov[w], distTow[w]);
			anc = w;
		}	
	}	
	// BFS from vertices of ww; change distTo to hold the maximum between distTov and distTow and remember a vertex where distTo is minimum
	int w;
	while (!q.empty()) {
		w = q.front();
		q.pop();
		for (int u : G.adjV(w)) 
			if (!marked[u]) {
				q.push(u);
				marked[u] = true;
				distTow[u] = 1 + distTow[w];
				if (dmin > max(distTov[u], distTow[u])) {
					dmin = max(distTov[u], distTow[u]);
					anc = u;
				}
			}
	}
	if (dmin != G.numV())
		return anc;
	else
		return -1;
}
