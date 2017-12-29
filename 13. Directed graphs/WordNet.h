#ifndef WORD_NET
#define WORD_NET

#include "Digraph.h"
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;

class WordNet {
	public:
		WordNet(const string &, const string &);
		bool isNoun(const string &word) const { 
			return (words.find(word) != words.end()); 
		};
		vector<string> nouns() const;
		int distance(const string &, const string &) const;
		vector<string> sap(const string &, const string &) const;
		string outcast(const vector<string> &items) const;		
	private:
		vector<int> idWordNet(const string &word) const {
			map<string, vector<int>>::const_iterator it = words.find(word);
			if (it != words.end())
				return it->second;
			else
				return vector<int>();				
		};
		
		map<string, vector<int>> words;	
		Digraph G;
};


#endif