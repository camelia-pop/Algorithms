#include "Digraph.h"
#include "DirectedCycle.h"
//#include "SCC.h"
#include "TopologicalSort.h"
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;

int main() {
	ifstream is("Acyclic_graph2.txt");
	Digraph G(is);
	is.close();
	cout << "G is a DAG? " << G.isDAG() << endl;
	cout << "G in reversed post order: ";
	stack<size_t> st = G.reversedPostOrder();
	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
	
	if (G.isDAG()) {
		cout << "G has a Hamiltonian path? " << G.hasHamiltonianPath() << endl;
		if (G.hasReachableVertexDAG()) 
			cout << "G has a reachable vertex: " << G.reachableVertexDAG() << endl;
		else
			cout << "G does not have a reachable vertex" << endl;
	} else 
		cout << "G is not DAG" << endl;
	/*
	{
		SCC scc(G);
		if (scc.hasReachableVertex()) {
			cout << "G has a reachable vertex" << endl;
			cout << "The set of reachable vertices is: ";
			vector<size_t> vv(scc.reachableVertex());
			for (size_t v : vv)
				cout << v << " ";
			cout << endl;
		} else
			cout << "G does not have a reachable vertex";
	}
	*/
}