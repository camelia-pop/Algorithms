/*
Statement of the problem:
Cyclic rotations. Two strings s and t are cyclic rotations of one another if they have the same length and s consists of a suffix of t followed by a prefix of t. For example, "suffixsort" and "sortsuffix" are cyclic rotations.

Given N distinct strings, each of length L, design an algorithm to determine whether there exists a pair of distinct strings that are cyclic rotations of one another. For example, the following list of N = 12 strings of length L = 10 contains exactly one pair of strings ("suffixsort" and "sortsuffix") that are cyclic rotations of one another.

1 algorithms polynomial sortsuffix boyermoore
2 structures minimumcut suffixsort stackstack
3 binaryheap digraphdfs stringsort digraphbfs

The order of growth of the running time should be NL^2 (or better) in the worst case. Assume that the alphabet size R is a small constant.

Signing bonus. Do it in NL time in the worst case.

Solution:
For each word, form all its cyclic rotations. 
To form a cyclic rotation by copying the appropriate portions of the word it takes time proportional to L. 
Each word has L - 1 cyclic rotations, and so to form the vector of words and all their cyclic rotations, 
it takes time proportional to NL^2. If a cyclic rotation coincides with a cyclic rotation of the same word 
that has already been added to the vector, we ignore it. The vector of words and their cyclic rotations has size at most NL.

Order the vector of words and their cyclic rotations using LSD radix sort. 
If there are repetitions then there is a pair of words that are cyclic rotations of one another. Otherwise, there aren't. 
This operation takes time O(NL^2) (because R is assumed a fix constant).
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::vector;

void LSD_radix_sort(vector<string> &a, vector<string> &aux, size_t R, int d) {
	vector<int> count(R + 1, 0);
	for (size_t i = 0; i != a.size(); ++i)
		++count[a[i][d] - 'a' + 1];
	for (size_t i = 0; i != R; ++i)
		count[i + 1] += count[i];
	for (size_t i = 0; i != a.size(); ++i) 
		aux[count[a[i][d] - 'a']++] = a[i];		
	for (size_t i = 0; i != a.size(); ++i) 
		a[i] = aux[i];
}

void LSD_radix_sort(vector<string> &a, size_t R) {
	vector<string> aux(a.size());
	size_t L = a[0].size();
	for (int d = L - 1; d >= 0; --d) 
		LSD_radix_sort(a, aux, R, d);
}

void cyclic_rotations(vector<string> &a) {
	size_t n = a.size(), k = a.size(), L = a[0].size();
	for (size_t i = 0; i != n; ++i) {
		// l counts number of distinct cyclic rotations
		size_t l = 0;
		for (size_t j = 1; j != L; ++j) {
			string s = string(a[i].begin() + j, a[i].end()) 
					   + string(a[i].begin(), a[i].begin() + j);
			// check if cyclic rotation repeats
			bool cod = true;		
			if (s == a[i])
				cod = false;
			else 	
				for (size_t idx = 0; idx != l; ++idx)
					if (s == a[k + idx]) {
						cod = false;
						break;
					}
			if (cod) {	
				a.push_back(s);
				++l;
			}					
		}
		k += l;
	}
}

bool suffix_prefix(const vector<string> &a) {
	// add all cyclic rotations
	vector<string> cyc_rot = a;
	cyclic_rotations(cyc_rot);
	// sort vector of cyclic rotations
	size_t R = 26;
	LSD_radix_sort(cyc_rot, R);
	for (size_t i = 1; i != cyc_rot.size(); ++i)
		if (cyc_rot[i] == cyc_rot[i-1]) 
			return true;
	return false;
}

int main() {
	/* assume each string consists only of small letters (R = 26)
	and all strings have the same size LSD */
	// read input file
	ifstream is("strings.txt");
	vector<string> a;
	string s;
	while (is >> s)
		a.push_back(s);
	is.close();
	cout << "There is a pair of distinct strings that are cyclic rotations of one another? " << suffix_prefix(a) << endl;
}
