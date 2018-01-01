#ifndef MONOTONE_SHORTEST_PATH_H
#define MONOTONE_SHORTEST_PATH_H

//#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include "IndexPQ.h"
#include <algorithm>
#include <functional>
#include <limits>
#include <stack>
#include <vector>

using std::less;
using std::numeric_limits;
using std::sort;
using std::stack;
using std::vector;

/*
1. Monotonic shortest path. 

Given an edge-weighted digraph G, design an Elog(E) algorithm to find a monotonic shortest path from s to every other vertex. A path is monotonic if the sequence of edge weights along the path are either strictly increasing or strictly decreasing.

Idea of the solution:
In Dijkstra's shortest path algorithm we form a priority queue consisting of vertices ordered by the length of the path to the source.

The difference between finding shortest paths and monotone shortest paths is illustrated in the following example. In the digraph:
0 1 0.5
0 3 0.8
1 2 1.1
3 2 0.9
2 4 1

the shortest path to 2 is 0 - 1 - 2 and the shortest path to 4 is 0 - 1 - 2 - 4,
but the monotone SP to 2 is 0 - 1 - 2, while the monotone SP to 4 is 0 - 3 - 2 - 4.
The two monotone shortest paths intersect at 2, but they are different before 2, while the regular shortest paths again intersect at 2 and they coincide before that.

Thus, the vector edgeTo[v] in Dijkstra's SP algorithm is no longer well-defined for the monotone SP. (In the example above, edgeTo[2] takes value 1 for the monotone shortest path leading to 2 and 3 for the monotone shortest path leading to 4.)

The idea is to associate to each edge of the graph an index 0, 1, ..., E-1, and hold in the IndexPQ these indices (practically the corresponding edges) and choose the key to be the length of the path needed to reach the corresponding edge.

To remember how to return from an edge to the source we hold the vector backEdge[i], which for an index i (practically the corresponding edge) gives us the index of the best previous edge before i to return to the source.

Also for a vertex v we need to remember along which edge to return. For this we define backVertex[v], which for a vertex v gives us the index of the edge to return along to the source.
*/

template <typename Comparator = less<double>>
class MonotoneSP {
	public:
		MonotoneSP(const EdgeWeightedDigraph &G, int s = 0, const Comparator &c = Comparator());
		inline bool hasPathTo(int) const;
		vector<DirectedEdge> pathTo(int) const;
	private:
		Comparator comp;
		IndexPQ<double, less<double>> pq;
		vector<DirectedEdge> indexToEdge;
		vector<double> distTo;
		vector<int> backEdge;
		vector<vector<int>> vertexOutgoingEdge;
		vector<int> backVertex;	
};

template <typename Comparator>
MonotoneSP<Comparator>::MonotoneSP(const EdgeWeightedDigraph &G, int s, const Comparator &c):
	comp(c),
	pq(G.numE()),
	distTo(G.numV(), numeric_limits<double>::max()),
	backEdge(G.numE(), -1),
	vertexOutgoingEdge(G.numV(), vector<int>()),
	backVertex(G.numV(), -1) {
	/* Step 1. Preprocessing: 
				- create indexToEdge[] which is a bijective function from the set {0, 1, ..., E-1} to the set of all edges of the graph;
				- order indexToEdge[] by the weights of the edges;
				- create vertexOutgoingEdge[] which for each vertex 0, 1, ..., V-1 holds a vector of the indices in indexToEdge[] corresponding to the outgoing edges from that particular vertex; these will be ordered by their weight;
				- backEdge[] of an index holds the index of the previous edge in the Monotonic SP;
				- backVertex[] of a vertex holds the index of the edge along which we need to return to arrive at the source;
				- being initialized by -1 means that we didn't reach that particular index of the edge (in backEdge[]) or vertex (in backVertex[])
				- IndexPQ pq will hold indices from 0, 1, ..., E-1 (which is equivalent to holding an edge) and the key is the length of the path taken to arrive at that edge
	*/
	// order the outgoing edges for each vertex by their weight
	// create indexToEdge[]
	for (int v = 0; v != G.numV(); ++v)
		for (DirectedEdge e : G.outgoingEdges(v)) 
			indexToEdge.push_back(e);
	sort(indexToEdge.begin(), indexToEdge.end(), 
		[&](const DirectedEdge &e1, const DirectedEdge &e2) 
		{ return comp(e1.weight(), e2.weight()); });
	
	// create vertexOutgoingEdge[]	
	for (size_t i = 0; i != indexToEdge.size(); ++i) 
		// vertexOutgoingEdge[v] is a vector that holds the indices of all outgoing edges from v ordered by their weight;
		vertexOutgoingEdge[indexToEdge[i].from()].push_back(i);
	
	/* Step 2: initialize the IndexPQ pq with all the edges emerging from 
			   the source s;
	*/
	vector<int> idxVec = vertexOutgoingEdge[s];
	DirectedEdge e;
	distTo[s] = 0.0;
	for (size_t i = 0; i != idxVec.size(); ++i) {
		e = indexToEdge[idxVec[i]];
		distTo[e.to()] = e.weight();
		backVertex[e.to()] = idxVec[i];
		pq.insert(idxVec[i], e.weight());
	}
	/*	Step 3: loop through that IndexPQ choosing an edge only if the 			monotonicity condition is satisfied;
	*/
	double currLength;
	int idxCurrEdge, idxNextEdge, currVertex, nextVertex;
	DirectedEdge currEdge, nextEdge;
	vector<int> idxOutgoingEdges;
	while (!pq.isEmpty()) {
		// remove the top index of the top edge from the PQ
		currLength = pq.topKey();
		idxCurrEdge = pq.removeTop();
		currEdge = indexToEdge[idxCurrEdge];
		currVertex = currEdge.to();
		// check all emerging edges from currVertex
		idxOutgoingEdges = vertexOutgoingEdge[currVertex];
		// relaxation step -- iterate through the outgoing edge in descending order and stop the first time the addition of the weight of the outgoing edge doesn't result in a monotone path
		size_t k = idxOutgoingEdges.size();
		while (k > 0) {
			--k;
			idxNextEdge = idxOutgoingEdges[k];
			nextEdge = indexToEdge[idxNextEdge];
			nextVertex = nextEdge.to();
			// break when monotonicity is not satisfied
			if (!comp(currEdge.weight(), nextEdge.weight()))
				break;
			// relax nextEdge	
			if (distTo[nextVertex] > distTo[currVertex] + nextEdge.weight()) {
				distTo[nextVertex] = distTo[currVertex] + nextEdge.weight();
				backEdge[idxNextEdge] = idxCurrEdge;
				backVertex[nextVertex] = idxNextEdge;
				if (pq.contains(idxNextEdge)) 
					pq.changeKey(idxNextEdge, distTo[nextVertex]);
				else 
					pq.insert(idxNextEdge, distTo[nextVertex]);
			} else 
				if (pq.contains(idxNextEdge)) {
					if (comp(currLength + nextEdge.weight(), pq.keyAt(idxNextEdge))) {
						backEdge[idxNextEdge] = idxCurrEdge;
						pq.changeKey(idxNextEdge, currLength + nextEdge.weight());	
					}
				} else {
					backEdge[idxNextEdge] = idxCurrEdge;
					pq.insert(idxNextEdge, currLength + nextEdge.weight());
				}
		}		
	}
}


template <typename Comparator>	
inline bool MonotoneSP<Comparator>::hasPathTo(int v) const {
	if ((v < 0) || (v >= backVertex.size()))
		return false;
	return (backVertex[v] != -1);
}

template <typename Comparator>
vector<DirectedEdge> MonotoneSP<Comparator>::pathTo(int v) const {
	if (!hasPathTo(v))
		return vector<DirectedEdge>();
	stack<int> st;
	int i = backVertex[v];
	while (i != -1) {
		st.push(i);
		i = backEdge[i];
	}
	vector<DirectedEdge> links;
	while (!st.empty()) {
		links.push_back(indexToEdge[st.top()]);
		st.pop();
	}
	return links;
}

#endif