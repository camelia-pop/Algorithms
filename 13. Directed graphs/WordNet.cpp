#include "SAP.h"
#include "WordNet.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::cout;
using std::endl;
using std::find;
using std::ifstream;
using std::istringstream;
using std::stoi;

WordNet::WordNet(const string &synsets, const string &hypernyms): G(0) {
	ifstream is(synsets);
	string s;
	int n, V(0);
	map<string, vector<int>>::iterator it;
	while (getline(is, s, ',')) {	
		n = stoi(s);
		if (V < n)
			V = n;
		getline(is, s, ',');
		istringstream set_of_words(s);
		while (set_of_words >> s) {
			it = words.find(s);
			if (it != words.end())
				it->second.push_back(n);
			else
				words.insert({s, vector<int>(1, n)});
		}
		getline(is, s);
	}
	++V;
	is.close();
	
	is.open(hypernyms);
	Digraph Gaux(V);
	while (getline(is, s, ',')) {	
		size_t v = stoi(s);
		getline(is, s);
		istringstream set_of_vertices(s);
		while (getline(set_of_vertices, s, ',')) 
			Gaux.addEdge(v, stoi(s));
	}
	G = Gaux;
	is.close();
}

vector<string> WordNet::nouns() const {
	vector<string> dict_words;
	dict_words.reserve(G.numV());
	for (auto it = words.cbegin(); it != words.cend(); ++it)
		dict_words.push_back(it->first);
	return dict_words;
}

int WordNet::distance(const string &nounA, const string &nounB) const {
	if (!isNoun(nounA) || !isNoun(nounB)) {
		cout << "At least one of the words is not found" << endl;
		return -1;
	}
	return SAP(G).length(idWordNet(nounA), idWordNet(nounB));	
}

vector<string> WordNet::sap(const string &nounA, const string &nounB) const {
	if (!isNoun(nounA) || !isNoun(nounB)) {
		cout << "At least one of the words is not found" << endl;
		return vector<string>();
	}
	SAP anc(G);
	int id = anc.ancestor(idWordNet(nounA), idWordNet(nounB));
	if (id == -1) 
		return vector<string>();
	vector<string> common_anc;
	for (auto it = words.cbegin(); it != words.cend(); ++it)
		if (find(it->second.cbegin(), it->second.cend(), id) 
				!= it->second.cend())
			common_anc.push_back(it->first);
	return common_anc;
}

string WordNet::outcast(const vector<string> &items) const {
	for (size_t i = 0; i != items.size(); ++i) 
		if (!isNoun(items[i])) {
			cout << "Found word not in WordNet" << endl;
			return "";
		}
	int d = 0, k;
	for (size_t i = 0; i != items.size(); ++i) {
		int dcurr = 0;
		for (size_t j = 0; j != items.size(); ++j) 
			dcurr += distance(items[i], items[j]);
		if (dcurr > d) {
			d = dcurr;
			k = i;
		}	
	}
	return items[k];
}
