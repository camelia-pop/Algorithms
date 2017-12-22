/*
1. 4-SUM. Given an array a[] of n integers, the 4-SUM problem is to determine if there exist distinct indices i, j, k, and l 
such that a[i]+a[j]=a[k]+a[l]. Design an algorithm for the 4-SUM problem that takes time proportional to n^2 
(under suitable technical assumptions).

Solution:
We compute each sum of two elements and we enter it into an unordered set. 
Before including the two sum into the unordered set, we check if the sum is already contained there, 
which means that we found indices i, j, k, l such that a[i] + a[j] = a[k] + a[l] (assuming that the array a[] contains no repetitions).

Unordered sets are implemented using hash tables, and so the checking if a sum is contained in the set takes constant time, 
under the uniform hashing assumption.

To find the indices that have equal two sums, we use on unordered multi-map using
key = two sum 
and 
value = a set of pairs (i, j) such that a[i] + a[j] = key.
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::unordered_map;
using std::unordered_set;
using std::vector;

bool fourSumExist(const vector<int> &a) {
	unordered_set<int> s;
	for (vector<int>::size_type i = 0; i != a.size(); ++i)
		for (vector<int>::size_type j = i + 1; j != a.size(); ++j)
			if (s.find(a[i] + a[j]) != s.end()) 
				return true;
			else
				s.insert(a[i] + a[j]);
	return false;		
}

void fourSum(const vector<int> &a, 
             unordered_map<int, vector<pair<int, int>>> &m) {
	for (vector<int>::size_type i = 0; i != a.size(); ++i)
		for (vector<int>::size_type j = i + 1; j != a.size(); ++j) {
			int sum = a[i] + a[j];
			if (m.find(sum) == m.end()) 
				m.insert({sum, vector<pair<int, int>>()});
			m[sum].push_back({i, j});			
		}
}

void fourSum(const vector<int> &a) {
	unordered_map<int, vector<pair<int, int>>> m;
	fourSum(a, m);
	for (auto it = m.begin(); it != m.end(); ++it) {
		if (it->second.size() >= 2) {
			cout << "Sum " << it->first << ":\n\t indices: ";
			for (auto itv = it->second.begin(); 
			          itv != it->second.end(); ++itv)
				cout << "(" << itv->first << ", " << itv->second << ") ";
			cout << endl << endl;		
		}
	}
}

int main() {
	vector<int> a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	cout << "Vector a: ";
	for_each(a.begin(), a.end(), [](const int i) { cout << i << " ";});
	cout << endl << endl;
	
	cout << "There are i, j, k, l such that a[i] + a[j] = a[k] + a[l]? " << (fourSumExist(a)? "True" : "False") << endl << endl;
	
	fourSum(a);
}
