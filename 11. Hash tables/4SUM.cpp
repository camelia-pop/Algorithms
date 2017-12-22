/*
1. 4-SUM. Given an array a[] of n integers, the 4-SUM problem is to determine if there exist distinct indices i, j, k, and l 
such that a[i]+a[j]=a[k]+a[l]. Design an algorithm for the 4-SUM problem that takes time proportional to n^2 
(under suitable technical assumptions).

Solution:
For all indices (i, j), such that 1 <= i < j <= n, put the sum a[i] + a[j] into an ordered array. 
This can be done using the same method that we used in the solution of the 3-SUM problem. 
It requires O(n^2) operations.

Then traverse the ordered array of sums and check for repetitions.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::vector;

/*******************************************************
F creates a vector
that holds the sum of 2 distinct elements from 
an array a[]. The sums are stored in the vector sum[], 
which is sorted in increasing order (the input vector 
a[] is also assumed increasingly ordered). The vector of
pairs pr[] holds in position i the indices of the elements
of the vector a[] that sum up to sum[i].
*********************************************************/

// a[] is non-decreasingly ordered
void twoSum(const vector<int> &a, 
			vector<int> &sum, 
			vector<pair<int, int>> &pr) {	
	int n = a.size();
	vector<int> ind;
	for (int i = 0; i != n; ++i) 
		ind.push_back(i + 1);
	int i = 0, s, s0, s1, s2, j;
	
	while (i < n-2) {
		s = a[i] + a[ind[i]];
		s0 = a[i+1] + a[ind[i+1]];
		while ((s <= s0) && (i < n-2)) {
			sum.push_back(s);
			pr.push_back({i, ind[i]});
			++ind[i];
			if (ind[i] == n) {
				++i;
				if (i != n-2) 
					s0 = a[i+1] + a[ind[i+1]];
			}
			s = a[i] + a[ind[i]];
		}
		if (i == n-2) {
			sum.push_back(s);
			pr.push_back({i, ind[i]});
		} else {
			j = i + 1;
			while (j < n-2) {
				s1 = a[j] + a[ind[j]];
				s2 = a[j+1] + a[ind[j+1]];
				while ((s1 <= s2) && (s1 <= s)) {	
					sum.push_back(s1);
					pr.push_back({j, ind[j]});
					++ind[j];
					s1 = a[j] + a[ind[j]];
				}
				++j;
			}
		}
	}
}

// a[] is non-decreasigly ordered
void fourSum(const vector<int> &a,
			 vector<int> &distinct_sums,
			 vector<vector<pair<int, int>>> &pairs){
	vector<int> sum;
	vector<pair<int, int>> pr;
	twoSum(a, sum, pr);
		
	int i(0), j(0), k(0), m(sum.size());
	while (i != m) {
		j = i; ++i;
		while ((i != m) && (sum[i] == sum[j])) ++i;
		if (i-1 != j) {
			distinct_sums.push_back(sum[j]);
			pairs.push_back(vector<pair<int, int>>());
			for (vector<pair<int, int>>::size_type l = j; l != i; ++l)
				pairs[k].push_back(pr[l]);
			++k;			
		}
	}
}

void fourSum(vector<int> a) {
	sort(a.begin(), a.end());
	vector<int> distinct_sums;
	vector<vector<pair<int, int>>> pairs;
	fourSum(a, distinct_sums, pairs);
	// print result
	for (size_t i = 0; i != distinct_sums.size(); ++i) {
		cout << "Pairs for sum " << distinct_sums[i] << ": ";
		for (size_t j = 0; j != pairs[i].size(); ++j)
			cout << "(" << pairs[i][j].first << ", " 
				 << pairs[i][j].second << ") ";
		cout << endl;		 
	}	
}

int main() {
	vector<int> a = {-2, -1, 0, 1, 2, 3, 4, 5, 6};
	cout << "Vector a: ";
	for_each(a.begin(), a.end(), [](const int i) { cout << i << " ";});
	cout << endl << endl;
	fourSum(a);	
}
