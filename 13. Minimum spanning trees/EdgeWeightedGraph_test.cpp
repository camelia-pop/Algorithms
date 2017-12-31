#include "Edge.h"
#include "EdgeWeightedGraph.h"
#include "IndexPQ.h"
#include "MST.h"
#include <fstream>
#include <functional>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;
using std::greater;

int main() {
	Edge e1(3, 4, 5), e2(2, 3,75);
	cout << "e1: " << e1.to_string() << endl;
	cout << "e2: " << e2.to_string() << endl << endl;
	
	ifstream is("EdgeWeightedGraph.txt");
	EdgeWeightedGraph G(is);
	is.close();
	G.addEdge(Edge(0, 3, 0.70));
	cout << "Edge weighted graph: " << endl;
	print(cout, G) << endl;
	
	IndexPQ<double> ipq(G.numV());
	ipq.insert(0, 0.70);
	ipq.insert(1, 0.30);
	ipq.insert(2, 0.10);
	ipq.insert(3, 0.50);

	cout << "Index priority queue: " << endl;
	print(cout, ipq) << endl;
	cout << "Top key in index priority queue: " << ipq.topKey() << endl;
	cout << "Remove top key in index priority queue" << endl;
	ipq.removeTop();
	cout << "Top key in index priority queue: " << ipq.topKey() << endl;
	cout << "Remove top key in index priority queue" << endl;
	ipq.removeTop();
	cout << "Insert (1, 0.40) in index priority queue" << endl;
	ipq.insert(1, 0.40);
	cout << "Insert (2, 0.40) in index priority queue" << endl;
	ipq.insert(2, 0.20);
	cout << "Change key (0, 0.20) in index priority queue" << endl;
	ipq.changeKey(0, 0.20);
	cout << "Insert (4, 0.60) in index priority queue" << endl;
	ipq.insert(4, 0.60);
	cout << "Insert (5, 0.45) in index priority queue" << endl;
	ipq.insert(5, 0.45);
	cout << "Change key (3, 0.40) in index priority queue" << endl;
	ipq.changeKey(3, 0.40);
	cout << "Delete index 0 in index priority queue" << endl;
	ipq.deleteIndex(0);
	cout << "Index priority queue: " << endl;
	print(cout, ipq) << endl << endl;
	
	// Bottleneck minimum spanning tree (MST is also a bottleneck MST)
	MST<> mst(G);
	cout << "Minimum Spanning Tree G: " << endl;
	cout << "weight = " << mst.weight() << endl;
	cout << "Edges: " << endl;
	vector<Edge> vec = mst.edges();
	for (Edge e: vec)
		cout << e.to_string() << endl;

	// Is an edge in a MST?
	cout << "Edge (5, 7, 0.28) in MST? " << G.isInMST(Edge(5, 7, 0.28)) << endl;
	cout << "Edge (6, 3, 0.50) in MST? " << G.isInMST(Edge(6, 3, 0.50)) << endl;	
	cout << endl << endl;
	
	// Minimum-weight feedback edge set
	MST<greater<double>> max_st(G);
	cout << "Maximum Spanning Tree G: " << endl;
	cout << "Weight = " << max_st.weight() << endl;
	cout << "Edges: " << endl;
	vec = max_st.edges();
	for (Edge e: vec)
		cout << e.to_string() << endl;
	cout << endl;
	
	vector<Edge> edgesG = G.edges(), edgesMinFeedback;
	for (Edge e : edgesG) 
		if (find(vec.begin(), vec.end(), e) == vec.end())
			edgesMinFeedback.push_back(e);
	
	cout << "Edges in a minimum-weight feedback set: " << endl;
	for (Edge e : edgesMinFeedback)
		cout << e.to_string() << endl;	
	cout << endl;

}