/*
Statement of the problem:
Selection in two sorted arrays. Given two sorted arrays a[] and b[], of sizes n1 and n2, respectively, design an algorithm to find the k-th largest key. 
The order of growth of the worst case running time of your algorithm should be log n, where n = n1 + n2.

Version 1: n1 = n2 and k = n/2
Version 2: k = n/2
Version 3: no restrictions

Solution:
At each step, we divide at least one of the arrays in half.
For each array i = 1, 2, we keep in li the index of the first element in the subarray and in ri the index of the last element in the subarray, while mi is the middle point.
After division in half of each subarray, we figure out in which half subarray the k-th largest element needs to be. 
It takes log n1 steps to reduce the first array to a size 1 array, and it takes log n2 steps to reduce the second array to a size 1 array.
Thus, in total we do log n1 + log n2 operations, which is equivalent to O(log(n1 + n2)).
*/

#include <algorithm>
#include <iostream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::is_sorted;
using std::out_of_range;
using std::runtime_error;

int selection(const int[], const int[], const int, int, int, int, int);

int selection(const int a[], const int b[], const int n1, const int n2, const int k) {
	if ((k <= 0) || (k > n1 + n2)) 
		throw out_of_range("Out of range indices");
	if ((!is_sorted(a, a + n1)) || (!is_sorted(b, b + n2)))
		throw runtime_error("Array not sorted");
	return selection(a, b, k, 0, n1 - 1, 0, n2 - 1);
}

int selection(const int a[], const int b[], const int k, int l1, int r1, int l2, int r2) {
	int m1 = (l1 + r1) / 2;
	int	m2 = (l2 + r2) / 2;
	if (k < m1 + m2 + 2) {
		if (a[m1] <= b[m2]) {
			if (m2 == l2) return a[k - (m2 + 1)];
			else return selection(a, b, k, l1, r1, l2, m2 - 1);
		} 
		else {
			if (m1 == l1) return b[k - (m1 + 1)];
			else return selection(a, b, k, l1, m1 - 1, l2, r2);
		}
	}
	if (k > m1+m2+2) {
			if (a[m1] <= b[m2]) {
			if (m1 == r1) return b[k - (m1 + 2)];
			else return selection(a, b, k, m1 + 1, r1, l2, r2);
		} 
		else {
			if (m2 == r2) return a[k - (m2 + 2)];
			else return selection(a, b, k, l1, r1, m2 + 1, r2);
		}
	}
	if (k == m1 + m2 + 2) {
		if (a[m1] < b[m2]) {
			if (m1 == r1) return b[m2];
			else return selection(a, b, k, m1 + 1, r1, l2, m2);
		}
		if (a[m1] == b[m2]) return b[m2];
		if (a[m1] > b[m2]) {
			if (m2 == r2) return a[m1];
			else return selection(a, b, k, l1, m1, m2 + 1, r2);
		}
	}	
}

int main() {
	int n1, n2, k;
	cout << "Size of the first array n1 =  ";
	cin >> n1; 
	cout << "Size of the second array n2 = ";
	cin >> n2; 
	cout << "Order of the element k = ";
	cin >> k;
		
	int a[n1]; 
	int	b[n2]; 
	cout << "Enter the elements of the first array: ";
	for (size_t i = 0; i != n1; ++i) 
		cin >> a[i];
	cout << "Enter the elements of the second array: ";
	for (size_t i = 0; i != n2; ++i) 
		cin >> b[i];
	
	cout << "The value of the " << k <<"-th element: " << selection(a, b, n1, n2, k) << endl; 
}