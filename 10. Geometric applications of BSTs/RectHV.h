#ifndef RECTHV_H
#define RECTHV_H

#include "Point2D.h"
#include <math.h>

class RectHV {
	public:
		RectHV(double xxmin = 0.0, double yymin = 0.0,
		       double xxmax = 1.0, double yymax = 1.0) :
			   xmin(xxmin), ymin(yymin), xmax(xxmax), ymax(yymax) {};
		double x_min() const { return xmin; };
		double y_min() const { return ymin; };
		double x_max() const { return xmax; };
		double y_max() const { return ymax; };
		bool contains(const Point2D &P) const {
			return ((xmin <= P.x_coord()) && (P.x_coord() <= xmax)
			        && (ymin <= P.y_coord()) && (P.y_coord() <= ymax));
		};
		bool intersects(const RectHV &R) const {
			return (R.contains(Point2D(xmin, ymin)) 
					|| R.contains(Point2D(xmin, ymax)) 
					|| R.contains(Point2D(xmax, ymin))
					|| R.contains(Point2D(xmax, ymax)));
		};
		double distanceSquaredTo(const Point2D &P) const;
		double distanceTo(const Point2D &P) const {
			return sqrt(distanceSquaredTo(P));
		};
		bool operator==(const RectHV &R) const {
			return ((xmin == R.x_min()) && (xmax == R.x_max())
			        && (ymin == R.y_min()) && (ymax == R.y_max()));
		};
		string to_string() const {
			return Point2D(xmin, ymin).to_string() + " " 
			       + Point2D(xmax, ymax).to_string();
		};
	private:
		double xmin, ymin, xmax, ymax;
};

double RectHV::distanceSquaredTo(const Point2D &P) const {
	if (this->contains(P))
		return 0.0;
	if (P.x_coord() <= xmin) {
		if (P.y_coord() < ymin)
			return P.distanceSquaredTo(Point2D(xmin, ymin));
		if (P.y_coord() > ymax)
			return P.distanceSquaredTo(Point2D(xmin, ymax));
		return (xmin - P.x_coord()) * (xmin - P.x_coord());
	}
	if (P.x_coord() >= xmax) {
		if (P.y_coord() < ymin)
			return P.distanceSquaredTo(Point2D(xmax, ymin));
		if (P.y_coord() > ymax)
			return P.distanceSquaredTo(Point2D(xmax, ymax));
		return (P.x_coord() - xmax) * (P.x_coord() - xmax);
	}
	if (P.y_coord() > ymax) 
		return (P.y_coord() - ymax) * (P.y_coord() - ymax);
	return (ymin - P.y_coord()) * (ymin - P.y_coord());
}

#endif