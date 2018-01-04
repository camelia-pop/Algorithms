#include "FlowEdge.h"
#include "FlowNetwork.h"
#include "MaxFlow.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;

int main() {
	ifstream is("FlowNetwork.txt");
	FlowNetwork G(is);
	is.close();
	
	MaxFlow mf(G, 0, 5);
	cout << "Max flow: " << mf.totalFlow() << endl << endl;
	cout << "Vertices in the min-cut on the side of 0: " << endl;
	vector<int> mc = mf.minCut();
	for (int v : mc)
		cout << v << " ";
	cout << endl << endl;
	
	cout << "Flow network (edge, capacity, flow): " << endl;
	print(cout, G) << endl << endl;
}