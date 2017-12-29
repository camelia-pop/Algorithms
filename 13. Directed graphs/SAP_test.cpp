#include "Digraph.h"
#include "SAP.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;

int main() {
	ifstream is("Graph2.txt");
	Digraph G(is);
	is.close();
	SAP sap(G);
	
	size_t v = 3, w = 11;
	cout << "vertices: " << v << " " << w << endl;
	cout << "length " << sap.length(v, w);
	cout << " ancestor " << sap.ancestor(v, w) << endl << endl;
	
	v = 9; w = 12;
	cout << "vertices: " << v << " " << w << endl;
	cout << "length " << sap.length(v, w);
	cout << " ancestor " << sap.ancestor(v, w) << endl << endl;
		
	v = 7; w = 2;
	cout << "vertices: " << v << " " << w << endl;
	cout << "length " << sap.length(v, w);
	cout << " ancestor " << sap.ancestor(v, w) << endl << endl;
	
	v = 1; w = 6;
	cout << "vertices: " << v << " " << w << endl;
	cout << "length " << sap.length(v, w);
	cout << " ancestor " << sap.ancestor(v, w) << endl << endl;
	
	vector<int> vv = {0, 1, 2};
	vector<int> ww = {5, 6, 7};
	cout << "Vector 1: ";
	for (size_t i : vv)
		cout << i << " ";
	cout << endl;
	cout << "Vector 2: ";
	for (size_t i : ww)
		cout << i << " ";
	cout << endl;
	cout << "Length of the shortest ancestral path between vector 1 and vector 1: \n\t" << sap.length(vv, vv) << endl << endl;
	cout << "Length of the shortest ancestral path between between vector 1 and vector 2: \n\t" << sap.length(ww, vv) << endl << endl;
	
	cout << "Common ancestor that participates in a shortest ancestral path between between vector 1 and vector 1: \n\t" << sap.ancestor(vv, vv) << endl << endl;
	cout << "Common ancestor that participates in a shortest ancestral path between between vector 1 and vector 2: \n\t" << sap.ancestor(vv, ww) << endl << endl;
}