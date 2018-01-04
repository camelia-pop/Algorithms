#include "BaseballElimination.h"
#include "FlowNetwork.h"
#include "FlowEdge.h"
#include "MaxFlow.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::numeric_limits;
using std::string;

BaseballElimination::BaseballElimination(const string &fileName) {
	// read the input data
	ifstream is(fileName);
	is >> n;
	string s;
	int k;
	for (size_t i = 0; i != n; ++i) {
		is >> s; tm.push_back(s);
		is >> k; w.push_back(k);
		is >> k; l.push_back(k);
		is >> k; r.push_back(k);
		vector<int> vec;
		for (size_t j = 0; j != n; ++j) {
			is >> k; vec.push_back(k);
		}
		g.push_back(vec);	
	}
	is.close();
	
	elim = vector<bool>(n);
	playersLeadingToElim = vector<vector<int>>(n, vector<int>());
	
	// for each team, create a FlowNetwork and run MaxFlow	
	// number of vertices in FlowNetwork
	int V = ((n-1) * n) / 2 + n + 2;
	// the terminal vertex end = 0 and the start vertex start = V - 1;
	int end = 0, start = V - 1, ctr;
	double inf = 99;//= numeric_limits<double>::max();
	for (size_t i = 0; i != n; ++i) {
		// create FlowNetwork for team i
		FlowNetwork fn(V);
		for (size_t j = 0; j != n; ++j) {
			if (j == i) continue;
			fn.addEdge(FlowEdge(j+1, end, w[i] + r[i] - w[j]));
		}
		ctr = n + 1;	
		for (size_t j = 0; j != n; ++j) {
			if (j == i) {
				ctr += n - i - 1;
				continue;
			}
			for (size_t k = j + 1; k != n; ++k) {
				if (k == i) {
					++ctr;
					continue;
				}
				fn.addEdge(FlowEdge(ctr, j+1, inf));
				fn.addEdge(FlowEdge(ctr, k+1, inf));
				fn.addEdge(FlowEdge(start, ctr, g[j][k]));
				++ctr;
			}
		}
		// create MaxFlow for the FlowNetwork for team i
		MaxFlow mf(fn, start, end);
		vector<int> minimumCut = mf.minCut();
		if (minimumCut.size() == 1) 
			// minCut contains only the start vertex
			elim[i] = false;
		else {
			elim[i] = true;
			for (int v : minimumCut)
				if ((v >= 1) && (v <= n))
					playersLeadingToElim[i].push_back(v - 1);
		}	
	}	
}

int BaseballElimination::wins(const string &teamName) const {
	for (size_t i = 0; i != tm.size(); ++i)
		if (tm[i] == teamName)
			return w[i];
	return -1;
}

int BaseballElimination::losses(const string &teamName) const {
	for (size_t i = 0; i != tm.size(); ++i)
		if (tm[i] == teamName)
			return l[i];
	return -1;
}

int BaseballElimination::remaining(const string &teamName) const {
	for (size_t i = 0; i != tm.size(); ++i)
		if (tm[i] == teamName)
			return r[i];
	return -1;
}

int BaseballElimination::against
	(const string &team1, const string &team2) const {
	int j = -1, k = -1;	
	for (size_t i = 0; i != tm.size(); ++i) {
		if (tm[i] == team1)
			j = i;
		else 
			if (tm[i] == team2)
				k = i;
	}
	if ((j != -1) && (k != -1))
		return g[j][k];
	return -1;	
}

bool BaseballElimination::isEliminated(const string &teamName) const {
	for (size_t i = 0; i != tm.size(); ++i)
		if (tm[i] == teamName)
			return elim[i];
	return false;
}

vector<string> BaseballElimination::certificateOfElimination
	(const string &teamName) const {
	vector<string> nameTeams;
	for (size_t i = 0; i != tm.size(); ++i)
		if (tm[i] == teamName) 
			for (int j : playersLeadingToElim[i]) 
				nameTeams.push_back(tm[j]);
	return nameTeams;
}