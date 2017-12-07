#include "BruteCollinearPoints.h"
#include "LineSegment.h"
#include "Point.h"
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main() {
	vector<Point> vp;
	vp.push_back(Point(6, 0));
	vp.push_back(Point(9, 0));
	vp.push_back(Point(3, 1));
	vp.push_back(Point(5, 2));
	vp.push_back(Point(8, 2));
	vp.push_back(Point(0, 3));
	vp.push_back(Point(7, 3));
	vp.push_back(Point(4, 4));
	vp.push_back(Point(9, 4));
	vp.push_back(Point(7, 4));
	vp.push_back(Point(11, 5));
	vp.push_back(Point(3, 6));
	vp.push_back(Point(6, 6));
	vp.push_back(Point(2, 8));
	
	vector<LineSegment> vecSeg = BruteCollinearPoints(vp).segments();
	cout << "Number of line segments: " << vecSeg.size() << endl << endl;
	cout << "Segments: " << endl;
	for (size_t i = 0; i != vecSeg.size(); ++i)
		cout << "\t" << vecSeg[i].toString() << endl;
	cout << endl;
}