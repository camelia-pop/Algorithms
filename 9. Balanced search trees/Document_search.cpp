/*
Statement of the problem:
Document search. Design an algorithm that takes a sequence of n document words and a sequence of m query words and find the shortest interval in which the m query words appear in the document in the order given. The length of an interval is the number of words in that interval.

Solution:
The document is given in document.txt.
The query words are given in query.txt.
Create a BST called document where the key is a word appearing in the text file and the value is a vector of indices in the text file where the word appears.
Create a vector of strings called query where that contains all the words in the query text file.
Create a vector v that contains at position i the vector of indices in the text file where the word query[i] appears.
Create a vector x such that x[i] is a position in the vector v[i] such that
v[i][x[i]] is an increasing sequence in i. The length v[m - 1][x[m - 1]] - v[0][x[0]] is equal to the length of a sequence in the text file where the words in the query appear (here m is the number of elements in the query). Find all vectors x with this property and choose the one with the smallest length.
*/

#include "BST.h"
#include <fstream>
#include <climits>
#include <string>
#include <vector>

using std::ifstream;
using std::string;
using std::vector;

int main() {
	BST<string, vector<int>> document;
	// create the document
	ifstream is;
	is.open("document.txt", ifstream::in);
	string word;
	size_t i = 0;
	while (is >> word) 
		if (document.find(word)) 
			(document.get(word)).push_back(++i);
		else 
			document.insert(word, vector<int>(1, ++i));
	is.close();
	
	// read the query
	is.open("query.txt");
	vector<string> query;
	while (is >> word) 
		query.push_back(word);
	is.close();
	
	// find the smallest interval for query
	size_t m = query.size();
	vector<vector<int>> v;
	for (size_t i = 0; i != m; ++i) 
		v.push_back(document.get(query[i]));
			
	vector<int> x(m, 0);
	int L = INT_MAX, Lnew;
	while (x[0] < v[0].size()) {
		size_t k = 0;
		while ((k < m-1) && (x[k] < v[k].size())) {
			while ((x[k+1] < v[k+1].size()) 
				    && (v[k][x[k]] > v[k+1][x[k+1]]))
						++x[k+1];
			++k;
		}
		if (x[m-1] < v[m-1].size()) {
			Lnew = v[m-1][x[m-1]] - v[0][x[0]];
			if (L > Lnew) L = Lnew;
		}
		++x[0];
	}
	if (L != INT_MAX) {
		cout << "Length of the smallest interval that contains the query: ";
		cout << L + 1 << endl;
	}
	else 
		cout << "The query was not found in the document" << endl;
}