#include "FlowEdge.h"
#include "FlowNetwork.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

FlowNetwork::FlowNetwork(ifstream &is) {
	is >> V;
	for (size_t i = 0; i != V; ++i)
		adj.push_back(vector<FlowEdge>());
	int vv, uu;
	double ww;
	while (is >> vv >> uu >> ww) {
		adj[vv].push_back(FlowEdge(vv, uu, ww, 0.0));
		adj[uu].push_back(FlowEdge(vv, uu, ww, 0.0));
		++E;
	}
}

void FlowNetwork::addEdge(const FlowEdge &e) {	
	adj[e.from()].push_back(e);
	adj[e.to()].push_back(e);
	++E;
}

void FlowNetwork::addFlow(const FlowEdge &e, int v, int u, double delta) {
	if ((e.from() == v) && (e.to() == u)) {
		for (FlowEdge &ee : adj[v])
			if ((ee.from() == v) && (ee.to() == u))
				ee.flow() += delta; 
		for (FlowEdge &ee : adj[u])
			if ((ee.from() == v) && (ee.to() == u))
				ee.flow() += delta; 
	} else {
		for (FlowEdge &ee : adj[u])
			if ((ee.from() == u) && (ee.to() == v))
				ee.flow() -= delta; 
		for (FlowEdge &ee : adj[v])
			if ((ee.from() == u) && (ee.to() == v))
				ee.flow() -= delta; 
	}		
}

vector<FlowEdge> FlowNetwork::adjEdges(int v) const {
	vector<FlowEdge> links;
	for (FlowEdge e : adj[v])
		links.push_back(e);
	return links;
}

ostream &print(ostream &os, const FlowNetwork &G) {
	os << G.numV() << endl << G.numE() << endl;
	for (size_t v = 0; v != G.numV(); ++v) {
		vector<FlowEdge> links = G.adjEdges(v);
		os << "Vertex " << v << endl;
		for (FlowEdge e : links)
			os << "\t" << e.to_string() << endl;
		cout << endl;
	}
	return os;
}