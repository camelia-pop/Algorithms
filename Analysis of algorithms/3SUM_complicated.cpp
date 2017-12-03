/*
Statement of the problem:
3-SUM in quadratic time. Design an algorithm for the 3-SUM problem that takes time proportional to n^2 in the worst case. 
You may assume that you can sort the n integers in time proportional to n^2 or better.

Solution: 
Create the vector of two sums ordered in increasing order using O(n^2) operations. This implementation uses extra memory proportional to n^2. Also it assumes that the input vector doesn't have repeating elements.

See a recursive implementation of the same algorithm in 3SUM_recursive.cpp.

See a better solution in 3SUM.cpp, which doesn't use extra memory. (This implementation is only for practice.)
*/

#include <algorithm>
#include <ctime>
#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::sort;
using std::vector;

// a[] is strictly increasing
/*
sum[] computes all the different sums of 2 elements;
pr[k] record the combination of indices (i, j) such that 
sum[k] = a[i] + a[j]  
*/
void twoSum(const vector<int> &a, vector<int> &sum, 
            vector<pair<int, int>> &pr) {	
	int n = a.size();
	vector<int> ind;
	for (int i = 0; i != n; ++i) 
		ind.push_back(i + 1);
	int i= 0, s, s0, s1, s2, j;
	
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

int threeSum(vector<int> a) {		
	vector<int> sum;
	vector<pair<int, int>> pr;
	sort(a.begin(), a.end());
	twoSum(a, sum, pr);
					  
	int i = 0, j = a.size(), k = 0;
	// traverse sum from left to right, and a in the opposite direction
	while ((i <= sum.size()-1) && (j >= 0)) 
		if (sum[i] + a[j] == 0) {
			if (pr[i].second < j) {
				cout << "Triple (" << pr[i].first << ", " 
				     << pr[i].second << ", " << j << ")" << endl;
				++k;
			}				
			++i;
		} else {
			if (sum[i] + a[j] > 0)
				--j;
			else
				++i;
		}
	
	return k;	
}

int main() {
	vector<int> a = {-2, -1, 0, 1, 2, 3, 4, 5, 6};
	cout << "Number of triples summing to 0: " << threeSum(a) << endl;
}






