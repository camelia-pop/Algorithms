/*
Statement of the problem:
Taxicab numbers. A taxicab number is an integer that can be expressed as the sum of two cubes of integers in two different ways: a^3 + b^3 = c^3 + d^3. 

For example, 1729 = 9^3 + 10^3 = 1^3 + 12^3. Design an algorithm to find all taxicab numbers with a, b, c, and d less than n.

Version 1: Use time proportional to n^2 log(n) and space proportional to n^2.

Version 2: Use time proportional to n^2 log(n) and space proportional to n.

Solution Version 1:

Create a point structure with coordinates (a, b), a < b, that take values from 1 to n (uses O(n^2) space). Put the points in a vector and order the points by a^3 + b^3 (uses O(n^2 log(n)) time). Keep the points that are adjacent to each other and have the same sum.

Solution Version 2:

Create a minPQ in which we first enqueue the points (i, i). We then delete the top element of the priority queue, say (i, j), and we add a new element (i, j + 1), when j < n. Whenever we encounter two consecutive elements taken from the priority queue with the same sum of cubes we add them to a vector where we keep the distinct points with equal sum.

*/

#include "PQ.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::greater;
using std::ostream;
using std::to_string;
using std::sort;
using std::string;
using std::vector;

class Point;

ostream &operator<<(ostream &, const Point &);

class Point {
	public:
		Point(size_t x, size_t y): a(x), b(y) {};
		size_t firstCoord() const { return a; };
		size_t secondCoord() const { return b; };
		size_t sum_cubes() const { return a * a * a + b * b * b; };
		bool operator<(const Point &P) const { 
			return sum_cubes() < P.sum_cubes(); 
		};
		bool operator>(const Point &P) const { 
			return sum_cubes() > P.sum_cubes(); 
		};
		bool operator==(const Point &P) const { 
			return ((a == P.a) && (b == P.b)); 
		};
		bool operator!=(const Point &P) const { 
			return (!this->operator==(P)); 
		};
		string toString() const { 
			return "(" + to_string(a) + ", " + to_string(b) + ")"; 
		};	
	private:	
		size_t a, b;
};

ostream &print(ostream &os, const vector<Point> &vp) {
	size_t i = 0, j, counter;
	while (i != vp.size()) {
		counter = 1;
		j = i + 1;
		while ((j != vp.size()) 
			    && (vp[i].sum_cubes() == vp[j].sum_cubes())) {
			++counter;	
			++j;
		}
		if (counter > 1) {
			os << "Sum of cubes " << vp[i].sum_cubes() << ": ";
			for (j = i; j != i + counter; ++j)
				os << vp[j].toString() << " ";
			os << endl;
		}
		i += counter; 
	}
	return os;
}

ostream &operator<<(ostream &os, const Point &P) {
	os << P.toString();
	return os;
}

// Version 1
vector<Point> taxicab(size_t n) {
	vector<Point> vp;
	for (size_t i = 1; i != n; ++i)
		for (size_t j = i + 1; j != n + 1; ++j)
			vp.push_back(Point(i, j));
	sort(vp.begin(), vp.end());
	return vp;
}

// Version 2
vector<Point> taxicabPQ(size_t n) {
	vector<Point> vp;
	
	PQ<Point, greater<Point>> pq;
	// initialize PQ
	for (size_t i = 1; i != n; ++i)
		pq.insert(Point(i, i));
	
	size_t counter = 1;
	Point prev(0, 0);	
	while (!pq.empty()) {
		Point curr = pq.top();
		pq.removeTop();
		if (curr.sum_cubes() == prev.sum_cubes()) {
			vp.push_back(curr);
			++counter;
			if (counter == 2)
				vp.push_back(prev);
		} else
			counter = 1;
		prev = curr;
		if (curr.secondCoord() < n)
			pq.insert(Point(curr.firstCoord(), curr.secondCoord() + 1));
	}
	return vp;
}

int main() {
	size_t n = 50;
	vector<Point> vp1(taxicab(n));
	cout << "Taxicab numbers using version 1 (n = " << n << "): " << endl;
	print(cout, vp1) << endl << endl;;
	
	cout << "Taxicab numbers using version 2 (n = " << n << "): " << endl;
	vector<Point> vp2(taxicabPQ(n));
	print(cout, vp2) << endl << endl;
}