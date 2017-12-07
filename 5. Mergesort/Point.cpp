#include "Point.h"

bool comparePoint(const Point &P1, const Point &P2) {
	return (P1.compareTo(P2)) ? true : false;
}

bool compareSlope(const Point &P, const Point &P1, const Point &P2) {
	return P.slopeOrder(P1, P2);
}
