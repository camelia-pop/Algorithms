#ifndef BRUTE_COLLINEAR_POINTS_H
#define BRUTE_COLLINEAR_POINTS_H

#include "LineSegment.h"
#include "Point.h"
#include <vector>

using std::vector;

class BruteCollinearPoints {
	public:
		BruteCollinearPoints(const vector<Point> &);
		size_t numberOfSegments() const { return numSeg; };
		vector<LineSegment> segments() const { return vecSeg; };
	private:
		size_t numSeg;
		vector<LineSegment> vecSeg;
};

#endif