#ifndef MAX_FLOW_H
#define MAX_FLOW_H

#include "FlowEdge.h"
#include "FlowNetwork.h"
#include <vector>

using std::vector;

class MaxFlow {
	public:
		MaxFlow(FlowNetwork &, int, int);
		double totalFlow() const { return value; };
		bool inMinCut(int v) const { return marked[v]; };
		vector<int> minCut() const;
	private:
		bool hasAugmentingPath(const FlowNetwork &, int, int);
		vector<bool> marked;
		vector<FlowEdge> edgeTo;
		double value;
};

#endif