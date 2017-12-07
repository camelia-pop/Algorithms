/*
Statement of the problem:
Counting inversions. An inversion in an array a[] is a pair of entries a[i] and a[j] such that i < j but a[i] > a[j]. 
Given an array design a linearithmic algorithm to count the number of inversions.

Solution: 
We will apply mergesort, which is a linearithmic algorithm.
In the merging procedure of two ordered arrays a[l], ... a[m], and a[m+1], ..., a[r], 
if we need to swap elements a[i] and a[j], it means that (i, j), (i + 1, j), ..., (m, j) are pairs of indices in an inversion. 
In total we have m - i + 1 inversions.
The total number of inversions = sum of the number of inversions we find when we have to do a swap in the merging procedure.
*/

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void merge(int a[], int aux[], int l, int m, int r, int &c) {
	for (int k = l; k <= r; ++k) aux[k] = a[k];	
	int i = l, j = m + 1;
	for (int k = l; k <= r; ++k) {
		if ((i <= m) && (j <= r)){
			if (aux[i] > aux[j]) { c += m - i + 1; a[k] = aux[j++]; }
			else a[k] = aux[i++];
		}
		else 
			if (i > m) a[k] = aux[j++];
				else a[k] = aux[i++];
	}	
}

void mergesort(int a[], int aux[], int l, int r, int &c) {
	if (l < r) {
		int m = (l + r) / 2;
		mergesort(a, aux, l, m, c);
		mergesort(a, aux, m + 1, r, c);
		merge(a, aux, l, m, r, c);
	}
}

int inversions(int a[], int n) {
	int c = 0;
	int aux[n];
	//copy a to another array so that we do not make the changes to a;
	int aa[n];
	for (int i = 0; i != n; ++i) aa[i] = a[i];	
 	mergesort(aa, aux, 0, n - 1, c);
	return c;
}

int main() {
	int n;
	cout << "Size of the array: "; 
	cin >> n;
	int a[n];
	cout << "Introduce the elements of the array: ";
	for (int i = 0; i != n; ++i) cin >> a[i];	
	cout << "Number of inversions in array: " << inversions(a, n) << endl;	
}
