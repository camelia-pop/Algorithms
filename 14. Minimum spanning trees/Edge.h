#ifndef EDGE_H
#define EDGE_H

#include <string>

using std::string;

class Edge {
	public:
		Edge(int vv, int uu, double ww): v(vv), u(uu), w(ww) {};
		double weight() const { return w; };
		int either() const { return v; };
		int other(int endpoint) const {return (endpoint == v) ? u : v; };
		string to_string() const { 
			return std::to_string(v) + " " + std::to_string(u) + " " + std::to_string(w); 
		};
		bool operator<(const Edge &e) const { return (w < e.w); };
		bool operator>(const Edge &e) const { return (w > e.w); };
		bool operator==(const Edge &e) const {
			return (w == e.w) 
			&& (((v == e.v) && (u == e.u)) || ((v == e.u) && (u == e.v)));
		};
	private:
		// endpoints
		int v, u;
		// weight
		double w;
};

#endif