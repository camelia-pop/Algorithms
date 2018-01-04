#ifndef BASEBALL_ELIMINATION_H
#define BASEBALL_ELIMINATION_H

#include "FlowNetwork.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class BaseballElimination {
	public:
		BaseballElimination(const string &);
		int numberOfTeams() const { return n; };
		vector<string> teams() const { return tm; };
		int wins(const string &) const;
		int losses(const string &) const;
		int remaining(const string &) const;
		int against(const string &, const string &) const;
		bool isEliminated(const string &) const;
		vector<string> certificateOfElimination(const string &) const;
	private:
		// data member for input data
		size_t n;
		vector<string> tm;
		vector<int> w, l, r;
		vector<vector<int>> g;
		// data members for output data
		vector<bool> elim;
		vector<vector<int>> playersLeadingToElim;		
};

#endif