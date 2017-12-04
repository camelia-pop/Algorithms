/*
Statement of the problem:
Intersection of two sets. 
Given two arrays a[] and b[], each containing n distinct 2D points in the plane, design a subquadratic algorithm to count the number of points that are contained both in array a[] and array b[].

Solution:
Sort the two arrays in lexicographic order using ShellSort (for Knuth sequence O(n^(3/2))). Then select the elements in common and place them in an array c[].
*/

#include "Point2D.h" 
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;


ostream &print(ostream &os, const vector<Point2D> &c) {
	for (size_t i = 0; i != c.size(); ++i)
		os << c[i] << endl;
	return os;
}

// shell sort with Knuth sequence h_0 = 1, h_n = 3 h_{n-1} + 1
template <typename T>
void shellsort(vector<T> &a) {
	int n = a.size(), h = 1;
	while (h < n/3) h = 3*h + 1;
	while (h >= 1) {
		for (size_t i = h; i != n; ++i) 
			for (size_t j = i; j >= h ; j -= h) 
				if (a[j - h] > a[j]) {
					T temp = a[j - h];
					a[j - h] = a[j];
					a[j] = temp;
				}					
		h = h / 3;		
	}	
}

vector<Point2D>  intersection(const vector<Point2D> &x, vector<Point2D> &y) {
	vector<Point2D> a = x, b = y;
	
	shellsort(a);
	shellsort(b);	
	
	vector<Point2D> c;
	size_t i = 0, j = 0, n = a.size(), m = b.size();
	for (size_t i = 0; i != a.size(); ++i) {
		while ((j != b.size()) && (b[j] < a[i]))
			++j;
		if (j == m)
			break;
		if (b[j] == a[i])
			c.push_back(a[i]);	
	}
	return c;
}

int main() {
	vector<Point2D> a;
	a.push_back(Point2D(2, 2));
	a.push_back(Point2D(1, 2));
	a.push_back(Point2D(4, 2));
	a.push_back(Point2D(2, 1));
	a.push_back(Point2D(7, 3));
	a.push_back(Point2D(3, -15));
	
	vector<Point2D> b;
	b.push_back(Point2D(4, 2));
	b.push_back(Point2D(2, 1));
	b.push_back(Point2D(4, 2));
	b.push_back(Point2D(2, 2));
	b.push_back(Point2D(7, 3));
	b.push_back(Point2D(30, -5));
	b.push_back(Point2D(23, -5));
	b.push_back(Point2D(-3, -5));
	
	vector<Point2D> c = intersection(a, b);
	cout << "Elements in common: " << endl; 
	print(cout, c) << endl;
	
}