#ifndef FAST_COLLINEAR_POINTS_H
#define FAST_COLLINEAR_POINTS_H

#include "LineSegment.h"
#include "Point.h"
#include <vector>

using std::vector;

class FastCollinearPoints {
	public:
		FastCollinearPoints(const vector<Point> &);
		size_t numberOfSegments() const { return numSeg; };
		vector<LineSegment> segments() const { return vecSeg; };
	private:
		size_t numSeg;
		vector<LineSegment> vecSeg;
};

#endif