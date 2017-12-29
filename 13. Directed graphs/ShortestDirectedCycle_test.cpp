#include "Digraph.h"
#include "DirectedCycle.h"
#include "ShortestDirectedCycle.h"
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;

int main() {
	
	ifstream is("Graph.txt");
	Digraph G(is);
	is.close();
	
	ShortestDirectedCycle sdc(G);
	cout << "Graph G has a directed cycle? " << sdc.hasCycle() << endl;
	if (sdc.hasCycle()) {
		cout << "A shortest directed cycle: ";
		vector<size_t> cycle(sdc.directedCycle());
		for (size_t v : cycle)
			cout << v << " ";
		cout << endl;
	}
	
	DirectedCycle dc(G);
	if (dc.hasCycle()) {
		cout << "A directed cycle: ";
		vector<size_t> cycle(dc.directedCycle());
		for (size_t v : cycle)
			cout << v << " ";
		cout << endl;
	}
}