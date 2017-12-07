#ifndef LINE_SEGMENT_H
#define LINE_SEGMENT_H

#include "Point.h"

class LineSegment {
	public:
		LineSegment(const Point &P1, const Point &Q1): P(P1), Q(Q1) {};
		// void draw();
		string toString() {
			return P.toString() + " -> " + Q.toString();
		};	
	private:
		Point P, Q;
};

#endif