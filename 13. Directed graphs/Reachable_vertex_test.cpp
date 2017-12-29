#include "Digraph.h"
#include "SCC.h"
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;

int main() {
	ifstream is("Graph1.txt");
	Digraph G(is);
	is.close();
	cout << "G is a DAG? " << G.isDAG() << endl;
	SCC scc(G);
	if (scc.hasReachableVertex()) {
		cout << "G has a reachable vertex" << endl;
		cout << "The set of reachable vertices: ";
		vector<size_t> vv(scc.reachableVertex());
		for (size_t v : vv)
			cout << v << " ";
		cout << endl;
	} else
		cout << "G does not have a reachable vertex";
}