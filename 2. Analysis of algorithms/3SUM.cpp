/*
Statement of the problem:
3-SUM in quadratic time. Design an algorithm for the 3-SUM problem that takes time proportional to n^2 in the worst case. 
You may assume that you can sort the n integers in time proportional to n^2 or better.

Solution:
The n integers are given in the sorted vector a[].
To find a sum of three elements a[i] + a[j] + a[k] = 0, we can assume
without loss of generality that i < j < k.
To search for such a sum we proceed as follows: For a fixed j = 1, 2, ..., n-2, we look for i = 0, 1, ..., n-1 and for k = n-1, n-2, ..., j+1.
	- When we find a sum a[i] + a[j] + a[k] > 0, the only way to bring the sum to 0 is to decrement k.
	- When we find a sum a[i] + a[j] + a[k] < 0, we could bring the sum to 0 by incrementing k (but the resulting sum was already considered) or by incrementing i. Thus the only non-examined case is the one when we increment i.
	- When we find a sum a[i] + a[j] + a[k] = 0, we found a valid set of indices (i, j, k), and we proceed to finding a new set of indices. We need to be careful how to increment i/decrement k so that we don't lose combination of indices when the vector a[] contains repeating elements.
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

int threeSum(vector<int> a) {
	sort(a.begin(), a.end());
	int ctr = 0, l;
	for (vector<int>::size_type j = 1; j < a.size(); ++j) {
		vector<int>::size_type i = 0, k = a.size() - 1;
		while ((i < j) && (j < k))
			if (a[i] + a[j] + a[k] > 0)
				--k;
			else if (a[i] + a[j] + a[k] < 0)
					++i;
				 else {
					if ((i + 1 < j) && (a[i] == a[i+1])) {
						l = k;
						while ((l > j) && (a[l] == a[k])) {
							cout << "Triple: (" << i << ", " << j << ", " << l << ")" << endl;
							++ctr;
							--l;
						}
						++i;
					} else {
						cout << "Triple: (" << i << ", " << j << ", " << k << ")" << endl;
						++ctr; 
					    --k;					
					}
				 } 		
	}
	return ctr;
}

int main() {
	vector<int> a = {-2, -2, -1, 0, 1, 1, 2, 3, 4, 5, 6};
	cout << "Number of triples summing to 0: " << threeSum(a) << endl;
}
