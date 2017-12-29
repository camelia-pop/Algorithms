#include "WordNet.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

int main() {
	WordNet wn("synsets50000-subgraph.txt", "hypernyms50000-subgraph.txt");
	cout << "casein0 found? " << wn.isNoun("casein0") << endl << endl;
	cout << "casein found? " << wn.isNoun("casein") << endl << endl;
	
	vector<string> dict_words(wn.nouns());
	cout << "number of words: " << dict_words.size() << endl;
	cout << endl;
	
	cout << "distance between antihaemophilic_factor and calcium_ion: " << wn.distance("antihaemophilic_factor", "calcium_ion") << endl << endl;
	
	vector<string> common_ancestor1(wn.sap("horse", "zebra"));
	cout << "common ancestor between horse and zebra: " << endl;
	for (string s : common_ancestor1)
		cout << s << " ";
	cout << endl << endl;
	
	vector<string> common_ancestor2(wn.sap("table", "zebra"));
	cout << "common ancestor between table and zebra: " << endl;
	for (string s : common_ancestor2)
		cout << s << " ";
	cout << endl << endl;
	
	vector<string> items;
	ifstream is("outcast11.txt");
	string s;
	while (getline(is, s))
		items.push_back(s);
	cout << "items: ";
	for (string s : items)
		cout << s << " ";
	cout << endl;
	cout << "outcast: ";
	cout << wn.outcast(items) << endl << endl;
}