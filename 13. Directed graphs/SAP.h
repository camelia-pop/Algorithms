#ifndef SHORTEST_ANCESTRAL_PATH
#define SHORTEST_ANCESTRAL_PATH

#include "Digraph.h"

class SAP {
	public:
		SAP(const Digraph &directedG): G(directedG) {}
		// length of shortest ancestral path between two vertices; -1 if no such path
		int length(int, int) const;
		// common ancestor that participates in a shortest ancestral path between two vertices; -1 if no such path
		int ancestor(int, int) const;
		// find two vertices in each vector that have the shortest ancestral path; return the length of this shortest ancestral path between two vertices; -1 if no such path
		int length(vector<int>, vector<int>) const;
		// find two vertices in each vector that have the shortest ancestral path; return their common ancestor; -1 if no such path
		int ancestor(vector<int>, vector<int>) const;
	private:
		Digraph G;
};

#endif
