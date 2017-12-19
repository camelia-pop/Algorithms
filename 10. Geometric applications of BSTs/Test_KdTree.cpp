#include "KdTree.h"
#include "Point2D.h"
#include "RectHV.h"
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;

int main() {
	KdTree A;
	// ifstream is("input1M.txt");
	ifstream is("input100K.txt");
	double x, y;
	while (is >> x >> y)  
		A.insert(Point2D(x, y));
	is.close();
	cout << "Size of set A = " << A.size() << endl;
	cout << "A contains point " << Point2D(0.320960, 0.221883) << "? "; 
	cout << A.contains(Point2D(0.320960, 0.221883)) << endl;
	
	RectHV R(0.605283, 0.212412, 0.762514, 0.840319);
	cout << "Rectangle R: " << R.to_string() << endl;
	deque<Point2D> q(A.range(R));
	cout << "Number of points in R intersected with A (using range) = " << q.size() << endl;
	/*
	for (auto it = q.begin(); it != q.end(); ++it)
		cout << it->to_string() << endl;
	*/
	cout << "Number of points in R intersected with A (using range_count) = ";
	cout <<  A.range_count(R) << endl;
	
	Point2D P(A.nearest(Point2D(0.25, 0.25)));
	cout << "Nearest point in A to " << Point2D(0.25, 0.25) << ": " << P << endl;
	cout << "A contains point " << P << "? " << A.contains(P) << endl; 	
}
