/*
Statement of the problem:
Search in a bitonic array. An array is bitonic if it is comprised of an increasing sequence of integers followed immediately by a decreasing sequence of integers. 
Write a program that, given a bitonic array of n distinct integer values, determines whether a given integer is in the array.

Standard version: Use approx 3 * lg n compares in the worst case.

Signing bonus: Use 2 * lg n compares in the worst case (and prove that no algorithm can guarantee to perform fewer than 2 * lg n compares in the worst case).

Solution:
Find the delimination between the increasing and decreasing portions of the array doing binary search. pos is an index with the property that the array is increasing from 0 to pos, and it is decreasing from pos+1 to n-1. Then use binary search to find the key in the increasing array and in the decreasing array.
*/

#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

int search_delimitation(const vector<int> &a) {
	vector<int>::size_type left = 0, right = a.size() - 1, mid;
	while (left != right) {
		mid = (left + right) / 2; // round down, which means that mid could equal left, but mid will always be less that right (recall that right != left)
		if (a[mid] > a[mid + 1]) right = mid;
		else left = mid + 1;		
	}
	return right;
}

bool bin_search_decreasing
	(const vector<int> &a, 
	 vector<int>::size_type left, 
	 vector<int>::size_type right, 
	 int key) {
		 
	vector<int>::size_type mid;
	if (left > right) return false;
	while (left != right) {
		mid = (left + right) / 2; 		
		if (a[mid] > key) left = mid + 1;
		else right = mid;				
	}
	if (a[right] ==  key) return true;
	else return false;
}

bool bin_search_increasing(const vector<int> &a, 
	 vector<int>::size_type left, 
	 vector<int>::size_type right, 
	 int key) {
		 
	vector<int>::size_type mid;
	if (left > right) return false;
	while (left != right) {
		mid = (left + right) / 2; 		
		if (a[mid] >= key) right = mid;
		else left = mid + 1;				
	}
	if (a[right] ==  key) return true;
	else return false;
}


int main() {
	ifstream fin("Bitonic_array.txt"); // We read the array a from a text file. The first element is the key that we are searching in the array.
	int key;
	fin >> key;
	cout << "Key: " << key << endl << endl;
	
	vector<int> a;
	int elem;
    while (fin >> elem) a.push_back(elem);

	int pos = search_delimitation(a);
	
	cout << "Key in decreasing array: " 
		 << bin_search_decreasing(a, pos + 1, a.size() - 1, key)
	     << endl << endl;
	
	cout << "Key in increasing array: " 
	     << bin_search_increasing(a, 0, pos, key)
	     << endl << endl;
	
}