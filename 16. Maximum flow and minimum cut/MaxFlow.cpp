#include "FlowNetwork.h"
#include "MaxFlow.h"
#include <iostream>
#include <limits>
#include <queue>
#include <stdio.h>

using std::cout;
using std::endl;
using std::numeric_limits;
using std::queue;

MaxFlow::MaxFlow(FlowNetwork &G, int s, int t): 
	marked(G.numV()), edgeTo(G.numV()), value(0) {
	while (hasAugmentingPath(G, s, t)) {
		// find the flow that can be added to the augmenting path
		double bottle = numeric_limits<double>::max();
		for (int v = t; v != s; v = edgeTo[v].other(v)) {
			if (bottle > edgeTo[v].residualCapacityTo(v))
				bottle = edgeTo[v].residualCapacityTo(v);
		}	
		// add the flow to the augmenting path
		for (int v = t; v != s; v = edgeTo[v].other(v)) 
			G.addFlow(edgeTo[v], edgeTo[v].other(v), v, bottle);		
		// update total flow through the network
		value += bottle;
	}
}

// BFS to find an augmenting path
bool MaxFlow::hasAugmentingPath(const FlowNetwork &G, int s, int t) {
	for (size_t v = 0; v != G.numV(); ++v) 
		marked[v] = false;
	int v, u;
	queue<int> q;
	q.push(s);
	marked[s] = true;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (FlowEdge e : G.adjEdges(v)) {
			u = e.other(v);
			if ((e.residualCapacityTo(u)) && (!marked[u])) {
				q.push(u);
				edgeTo[u] = e;
				marked[u] = true;				
			}
		}
	}
	return marked[t];
}

vector<int> MaxFlow::minCut() const {
	vector<int> mc;
	for (int v = 0; v != marked.size(); ++v)
		if (marked[v])
			mc.push_back(v);
	return mc;
}