#ifndef FLOW_EDGE_H
#define FLOW_EDGE_H

#include <string>

using std::string;

class FlowEdge {
	public:
		FlowEdge(int vv = 0, int uu = 0, double c = 0.0, double fl = 0.0): v(vv), u(uu), cap(c), f(fl) {
			if ((f < 0.0) || (f > cap))
				f = 0.0;
		};
		int from() const { return v; };
		int to() const { return u; };
		int other(int w) const { return (w == v) ? u : v; };
		double capacity() const { return cap; };
		double &flow() { return f; };
		double residualCapacityTo(int w) const {
			return (w == u) ? cap - f : f;
		};
		// add flow toward w
		void addFlowTo(int w, double delta) {
			if (w == u) 	
				if ((delta > 0) && (f + delta <= cap))
					f = f + delta;
			if (w == v) 	
				if ((delta > 0) && (delta <= f))
					f = f - delta;	
		};		
		string to_string() const {
			return std::to_string(v) + "-" + std::to_string(u) + " " + std::to_string(cap) + " " + std::to_string(f);
		};
	private:
		int v, u;
		double cap, f;
};

#endif