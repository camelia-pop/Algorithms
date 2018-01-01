#ifndef DIJKSTRA_SHORTEST_PATH_H
#define DIJKSTRA_SHORTEST_PATH_H

#include "EdgeWeightedDigraph.h"
#include "IndexPQ.h"
#include <limits>
#include <vector>

using std::numeric_limits;
using std::vector;

class SP {
	public:
		SP(const EdgeWeightedDigraph &, int);
		double distanceTo(int v) const { return distTo[v]; };
		bool hasPathTo(int v) const { 
			return distTo[v] < numeric_limits<double>::max();
		};
		vector<DirectedEdge> pathTo(int) const;		
	private:
		void relaxEdge(const EdgeWeightedDigraph &, const DirectedEdge &);
		
		int source;
		IndexPQ<double> pqv;
		vector<double> distTo;
		vector<DirectedEdge> edgeTo;
};

#endif