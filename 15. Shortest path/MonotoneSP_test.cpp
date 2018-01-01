#include "MonotoneSP.h"
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>

using std::cout;
using std::endl;
using std::greater;
using std::ifstream;
using std::vector;

int main() {
	ifstream is("EdgeWeightedDigraph1.txt");
	EdgeWeightedDigraph G(is);
	is.close();
	cout << "Graph: " << endl;
	print(cout, G) << endl << endl;
	
	MonotoneSP<> msp(G);
	cout << "Monotone shortest path from 0 to 5? " << msp.hasPathTo(5) << endl;
	if (msp.hasPathTo(5)) {
		cout << "Monotone shortest path from 0 to 5: " << endl;
		vector<DirectedEdge> vec = msp.pathTo(5);
		for (DirectedEdge e : vec)
			cout << e.to_string() << endl;
		cout << endl;
	}
	cout << endl;
	
	cout << "Monotone shortest path from 0 to 4? " << msp.hasPathTo(4) << endl;
	if (msp.hasPathTo(4)) {
		cout << "Monotone shortest path from 0 to 4: " << endl;
		vector<DirectedEdge> vec = msp.pathTo(4);
		for (DirectedEdge e : vec)
			cout << e.to_string() << endl;
		cout << endl;
	}
	cout << endl;
}