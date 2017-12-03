/*
Statement of the problem:
3-SUM in quadratic time. Design an algorithm for the 3-SUM problem that takes time proportional to n^2 in the worst case. 
You may assume that you can sort the n integers in time proportional to n^2 or better.

Solution:
This is a recursive implementation of the algorithm used in 3SUM_complicated.cpp.

F() is a recursive function that creates a vector
that holds the sum[] of 2 distinct elements from 
an input vector a[]. The sums are stored in the vector sum[], 
which is sorted in increasing order (the input vector 
a[] is also assumed strictly increasingly sorted). The vector of
pairs pr[] holds in position i the indices of the elements
of the vector a[] that sum up to sum[i].

Similarly to 3SUM_complicated.cpp, this implementation uses extra memory proportional to n^2 and assumes that the input vector a[] has distinct elements.

See a better solution in 3SUM, which doesn't use extra memory. (This implementation is only for practice.)
*/


#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::min;
using std::pair;
using std::size_t;
using std::vector;

// Always i >= j; O(n^2)
void F(int i, int j, 
	   vector<pair<int, int>> &pr, 
	   vector<int> &sum, 
	   vector<int> &ind, 
	   const vector<int> &a) {
	vector<int>::size_type n = a.size();
	if (j == n - 2) {
		pr.push_back({n-2, n-1});
		sum.push_back(a[n-2] + a[n-1]);
		return;
	}
	if (i == j) {
		int snext = a[i+1] + a[ind[i+1]];
		int     s =	a[i] + a[ind[i]];
		while ((ind[i] <= n-1) && (s <= snext)) {	
			pr.push_back({i, ind[i]});
			sum.push_back(s);
			++ind[i];
			if (ind[i] <= n-1)
				s =	a[i] + a[ind[i]];
		}
		if (ind[i] == n)
			F(i+1, i+1, pr, sum, ind, a);
		else
			F(i+1, j, pr, sum, ind, a);
	} 
    if (i > j) {
		int snext = a[i+1] + a[ind[i+1]];
		int sbefore = a[j] + a[ind[j]];
		int     s =	a[i] + a[ind[i]];
		int s0 = min(snext, sbefore);
		while ((ind[i] <= n-1) && (s < s0)) {	
			pr.push_back({i, ind[i]});
			sum.push_back(s);
			++ind[i];
			if (ind[i] <= n-1)
				s =	a[i] + a[ind[i]];
		}
		if (snext < sbefore)
			F(i+1, j, pr, sum, ind, a);
		else
			F(j, j, pr, sum, ind, a);
	}
}

/***********************************************
Counts the number of triplets that sum up to zero.
pr holds the output from function F.
************************************************/

// O(n^2)
int count(const vector<pair<int, int>> &pr, const vector<int> &a) {
	int ctr = 0, m = pr.size(), n = a.size();
	int j = n-1, i = 0, val;
	while ((i != m) && ( j >= 0)) {
		val = a[pr[i].first] + a[pr[i].second];
		while ((j >= 0) && (a[j] > -val))
			--j;
		if (j >=0)
			if ((a[j] == -val) //&& (pr[i].first != j) 
				               && (pr[i].second < j)) {
				++ctr;
				cout << "(" << pr[i].first << ", " << pr[i].second 
				     << ", " << j << ") "  << endl;
			} 
		++i;
	}
	return ctr;
}

int threeSum(const vector<int> &a){
	vector<int> ind, sum;
	vector<pair<int, int>> pr;
	for (vector<int>::size_type i = 0; i != a.size(); ++i)
		ind.push_back(i + 1);
	sum.reserve((a.size() * (a.size() - 1)) / 2);
	pr.reserve((a.size() * (a.size() - 1)) / 2);
	
	F(0, 0, pr, sum, ind, a);
	
	return count(pr, a);
}

int main() {
	vector<int> a = {-2, -1, 0, 1, 2, 3, 4, 5, 6};
	cout << "Triplets that sum to zero: " << endl;
	cout << threeSum(a);
}
