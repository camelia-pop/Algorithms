#include "HamiltonianPath.h"
#include "TopologicalSort.h"

HamiltonianPath::HamiltonianPath(const Digraph &G): 
	revPostOrder(TopologicalSort(G).reversedPostOrder()),
	HamPathExists(true) {
	size_t v = revPostOrder.top();
	revPostOrder.pop();
	while (!revPostOrder.empty()) {
		size_t u = revPostOrder.top();
		revPostOrder.pop();
		if (!G.existsEdge(v, u)) {
			HamPathExists = false;
			break;
		}
		v = u;
	}	
}