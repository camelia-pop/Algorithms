/*
Statement of the problem:
Dutch national flag. 
Given an array of n buckets, each containing a red, white, or blue pebble, sort them by color. The allowed operations are:

swap(i, j): swap the pebble in bucket i with the pebble in bucket j.
color(i): color of pebble in bucket i.
The performance requirements are as follows:

At most n calls to color().
At most n calls to swap().
Constant extra space.

Solution:
0 = red; 1 = white; 2 = blue;
a[] is a vector of elements 0, 1, or 2
We arrange the colors in the order red, white, blue (0, 1, 2).
Traverse the array from left to right using the index i.
Invariant at step i is that all the red balls encountered up to that point occupy the first positions, and all the blue balls encountered up to step i are placed at the end of the array.
At step i, ir holds the position of the last red ball, and ib holds the position of the first blue ball from the end of the array.
*/

#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::swap;
using std::vector;

ostream &print(ostream &os, const vector<int> &c) {
	for (size_t i = 0; i != c.size(); ++i)
		os << c[i] << " ";
	return os;
}

void flag(vector<int> &a) {
	int ir = -1, ib = a.size(), i = 0;
	while (i != ib)
		switch (a[i]) {
			case 0: swap(a[++ir], a[i]); ++i; break;
			case 1: ++i; break;
			case 2: swap(a[i], a[--ib]); 
		}
}

int main() {
	vector<int> a = {0, 1, 0, 2, 1, 0, 2, 1, 0, 1, 0, 2, 2, 0, 0};
	cout << "Initial arrangement of colors: " << endl;
	print(cout, a) << endl << endl;
	flag(a); 
	cout << "New arrangement of colors: " << endl;
	print(cout, a) << endl << endl;
}