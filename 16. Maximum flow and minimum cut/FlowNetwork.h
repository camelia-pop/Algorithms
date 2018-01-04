#ifndef FLOW_NETWORK_H
#define FLOW_NETWORK_H

#include "FlowEdge.h"
#include <iostream>
#include <fstream>
#include <vector>

using std::ifstream;
using std::ostream;
using std::vector;

class FlowNetwork;

ostream &print(ostream &, const FlowNetwork &);

class FlowNetwork {
	public:
		FlowNetwork(int VV = 0): V(VV), E(0),
				adj(vector<vector<FlowEdge>>
				    (VV, vector<FlowEdge>())) {};
		FlowNetwork(ifstream &);
		int numV() const { return V; };
		int numE() const { return E; };
		void addEdge(const FlowEdge &);
		void addFlow(const FlowEdge &, int, int, double);
		vector<FlowEdge> adjEdges(int) const;
	private:
		int V, E;
		vector<vector<FlowEdge>> adj;
};

#endif