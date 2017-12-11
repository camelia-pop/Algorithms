/*
Statement of the problem:
Decimal dominants. Given an array with n keys design an algorithm to find all values that occur more than n/10 times. The expected running time of your algorithm should be linear.

Solution:
The same algorithm works if we want to find the elements that appear more than n/k times.
There can be at most k - 1 such elements.

We denote the given array by a[].
We define two arrays of length k - 1, which we denote e[] and o[].
In e[] we keep the elements that have the potential to appear more that n/k times.
In o[] we keep the number of occurrences of the corresponding element in e[]
(it is not quite the true occurrence of the element but something very similar).

We initialize all elements of o[] to zero.

We traverse the given array a[]. Say we are at a[k]. 
	1) If a[k] is already in e[] at some position i, we increment o[i].
	2) If a[k] is not in e[], but there is some position i with 
		o[i] = 	0, then we set e[i] = a[k] and increment o[i].
	3) If a[k] is not in e[], and every position i has o[i] > 0, then we decrement every o[i] by 1 (like Tetris), and we ignore a[i]. (This is the reason why o[] does not quite hold
	the number of occurrences of the corresponding element in e[].)
	
After we finish traversing the array a[], e[] will contain all the elements that appear more than n/k times, and possibly also elements that appear less than or equal to n/k times.

We find the occurrences in a[] of each element in e[] and we keep only those occuring more than n/k times.

The reason why the array e[] will contain all the elements occuring more than n/k times (good elements) is the following:

Imagine a histogram 1 2 ... k-1 k ... n, which should be an enumeration of the elements of the array a[]. The enumeration is such that it puts at the beginning the elements than appear more than n/k times (there may be fewer than k - 1).

Above each i we draw a rectangle with height equal to the number of times element i shows up in the array a[].


If a good element does not show up in the array e[], it can happen for two reasons:

	1) A good element E cannot be placed in e[]. This means that whenever we encounter E while traversing a[], the vector e[] is full and o[i] >= 1 for all i = 0, 1, ..., k - 1). But whenever we encountered E we decrease all o[i] by 1, and so all o[i] will be decreased at least n/k times. Thus o[i] remain positive only for those e[i] that are good elements. Since we could have added at most k - 2 good elements to e[] (at least one good element, E, was not added), there will be at least one index i such that o[i] == 0. Thus, at some point we will be able to add the good element E.
	
	2) A good element may have been added to e[], but then is deleted because many bad elements are encountered. (Below is just a rough argument why this cannot happen.)
	Assume that until the last good element was added, we have seen x bad elements. 
	Then o[i] for the good element is larger than n/k - x.
	The remaining number of elements is n/k - x. Whenever we encounter a bad element, o[i] decreases by 1, but in the end it is still positive, and so it cannot be removed by a bad element.					
*/

#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::for_each;
using std::vector;

vector<int> occurrences(const int a[], const int n, const int k) {
	size_t m = k - 1;
	vector<int> e(m), o(m, 0);
	for (size_t i = 0; i != n; ++i) {
		// check if a[i] is already in e[i]
		size_t j;
		for (j = 0; (j != m) && (e[j] != a[i]); ++j) {}
		if (j != m) // a[i] was found in e
			++o[j]; 
		else { // a[i] is not in e
			// find first j such that o[j] = 0;
			for (j = 0; (j != m) && o[j]; ++j) {}
			if (j == m) // decrease each o by 1 and don't add a[i] to e[]
				for_each(begin(o), end(o), [](int &occ) {--occ; });
			else { 	// add a[i] to e in position j
				e[j] = a[i]; 
				++o[j];				
			}									
		}
	}
	// traverse the array e[] and count the true number of times each element of e[] appears in the given array a[]
	for_each(begin(o), end(o), [](int &occ) {occ = 0; });
	for (size_t i = 0; i != n; ++i) {
		size_t j;
		for (j = 0; (j != m) && (e[j] != a[i]); ++j) {}
		if (j != m ) // a[i] was found in e[] at position j
			++o[j];
	}
	
	double f = (1.0 * n) / k;
	vector<int> frequentElements;
	for (size_t i = 0; i != m; ++i) 
		if (o[i] > f) 
			frequentElements.push_back(e[i]);
	return frequentElements;
}

int main() {
	int n, k;
	cout << "Size of the array n = "; 
	cin >> n;
	cout << "k =  "; 
	cin >> k;
	
	int a[n];
	cout << "Enter the elements of the array: ";
	for (size_t i = 0; i!= n; ++i) 
		cin >> a[i];
	
	vector<int> frequentElements = occurrences(a, n, k);
	if (!frequentElements.empty()) {
		cout << "The elements that appear more than " << (1.0 * n) / k <<" times: ";
		for_each(frequentElements.begin(), frequentElements.end(), 
				 [] (const int elem) { cout << elem << " "; });
		cout << endl << endl;
	} else 
		cout << "There are no elements that appear more than " << (1.0 * n) / k <<" times";
}