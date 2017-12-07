/*
Statement of the problem:
Merging with smaller auxiliary array. Suppose that the subarray a[0] to a[n−1] is sorted and the subarray a[n] to a[2∗n − 1] is sorted. 
How can you merge the two subarrays so that a[0] to a[2∗n − 1] is sorted using an auxiliary array of length n (instead of 2n)?

Solution:
Create an auxiliary array of size n where we copy the first half of the array. 
We then merge aux[] with the second half of the array a[] into a[]. 
*/

#include <algorithm>
#include <stdexcept>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::is_sorted;
using std::runtime_error;

void merge_helper(int a[], int aux[], int n) {
	size_t i = 0, j = n, N = 2*n;
	for (size_t k = 0; ((k != N) && (i != n)); ++k) {
		if ((j != N) && (aux[i] > a[j]) ) 
			a[k] = a[j++]; 
		else a[k] = aux[i++]; 
	}	
}

void merge(int a[], int n) {
	// check if each half of the arrays are sorted
	if (!is_sorted(a, a + n ))
		throw runtime_error("First half of the array is not sorted");
	if (!is_sorted(a + n, a + 2*n))
		throw runtime_error("Second half of the array is not sorted");
	// copy the first half of the array in an auxiliary array aux[]
	int aux[n];
	for (size_t k = 0; k != n; ++k) 
		aux[k] = a[k];
	// merge aux[] with the second half of a[] into a[]
	merge_helper(a, aux, n);
}


int main() {
	cout << "Number of elements in the first array: "; 
	int n;
	cin >> n;
	int a[2*n];
	cout << "Elements in the first half of the array: ";
	for (size_t i = 0; i!= n; ++i) cin >> a[i];
	cout << "Elements in the second half of the array: ";
	for (size_t i = n; i!= 2*n; ++i) cin >> a[i];
	
	merge(a, n);
	cout << "Merged array: ";
	for (size_t i = 0; i!= 2*n; ++i) cout << a[i] << " ";
	cout << endl;
}
