/*
Statement of the problem:
Permutation.  
Given two integer arrays of size n, design a subquadratic algorithm to determine whether one is a permutation of the other. 
That is, do they contain exactly the same entries but, possibly, in a different order.

Solution:
1. Sort the 2 arrays and then compare them. Implement shell sort with Knuth sequence defined recursively: h_0 = 1, h_n = 3*h_{n-1} + 1. Shell sort has subquadratic time O(n^(3/2)), where n is the size of the array.

2. If we are allowed to use extra space proportional to the size of the arrays and we can assume that the arrays contain distinct elements, then we can add the elements of the first array to an unordered set, and when we traverse the second array, we will check if each of its elements can be found in the set. This uses linear time.

We implement below the first solution.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::sort;
using std::swap;
using std::vector;

// Shell sort using Knuth sequence
void shellsort(vector<int> &a) {
	int n = a.size(), h = 1;
	while (h < n / 3) 
		h = 3*h + 1;
	while (h >= 1) {
		for (size_t i = 0; i != h; ++i)  
			// insertion sort of a[i], a[i+h], a[i+2h], ...
			for (size_t j = 1; i + j*h < n; ++j) {
				int k = j - 1;
				while ((k >= 0) && (a[i+k*h] > a[i+(k+1)*h])) { 	 	
					swap(a[i+k*h], a[i+(k+1)*h]);
					--k;					
				}
			}		
		h = h / 3;		
	}	
}

// Shell sort using Knuth sequence -- Coursera course implementation
void shellsort_from_course(vector<int> &a) {
	int n = a.size(), h = 1;
	while (h < n/3)
		h = 3*h + 1;
	while (h >= 1) {
		// insertion sort
		for (size_t i = h; i != n; ++i) 
			for (size_t j = i; j >= h ; j -= h) 
				if (a[j - h] > a[j])
					swap(a[j - h], a[j]);		
		h = h / 3;		
	}	
}

bool compare_arrays(vector<int> a, vector<int> b) {
	if (a.size() != b.size())
		return false;
	else {
		shellsort(a);
		shellsort(b);
		// shellsort_from_course(a);
		// shellsort_from_course(b);
		return (a == b);	
	}
}

int main() {
	vector<int> a {2, 4, 1, 2, -15, 2, 4, -5, 14, 2, 10, 23, 5, 3}, 
				b { 4, 2, 1, 7, -5, 2, 4, -15, 14, 2, 3, 23, 5, 10},
				c {2, 4, 1, 7, -15, 2, 4, -5, 14, 2, 10, 23, 5, 3};
	cout << "Compare arrays a and b: " << compare_arrays(a, b) << endl;
	cout << "Compare arrays b and c: " << compare_arrays(b, c) << endl;
}