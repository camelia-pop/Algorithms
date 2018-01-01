#ifndef DIRECTED_EDGE_H
#define DIRECTED_EDGE_H

#include <string>

using std::string;

class DirectedEdge {
	public:
		DirectedEdge(int vv = 0, int uu = 0, double ww = 0.0): 
			v(vv), u(uu), w(ww) {};
		double weight() const { return w; };
		int from() const { return v; };
		int to() const {return u; };
		string to_string() const { 
			return std::to_string(v) + " " + std::to_string(u) + " " + std::to_string(w); 
		};
		bool operator<(const DirectedEdge &e) const { return (w < e.w); };
		bool operator>(const DirectedEdge &e) const { return (w > e.w); };
		bool operator==(const DirectedEdge &e) const {
			return ((w == e.w) && (v == e.v) && (u == e.u)); 
		};
	private:
		int v, u;
		double w;
};

#endif