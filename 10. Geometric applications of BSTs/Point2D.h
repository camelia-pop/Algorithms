#ifndef POINT2D_H
#define POINT2D_H

#include <iostream>
#include <math.h>
#include <ostream>
#include <string>

using std::cout;
using std::endl;
using std::ostream;
using std::string;

class Point2D;

ostream &operator<<(ostream &, const Point2D &);

class Point2D {
	friend ostream &operator<<(ostream &, const Point2D &);
	public:
		Point2D(double xx = 0.0, double yy = 0.0): x(xx), y(yy) {
			if ((x < 0.0) || (x > 1.0) || (y < 0.0) || (y > 1.0)) {
				x = y = 0.0;
				cout << "Point not inside the unit square" << endl;
			}
		};
		double x_coord() const { return x; };
		double y_coord() const { return y; };
		double distanceSquaredTo(const Point2D &that) const {
			return (x - that.x) * (x - that.x) 
			        + (y - that.y) * (y - that.y);
		};
		double distanceTo(const Point2D &that) const {
			return sqrt(distanceSquaredTo(that));
		};
		bool operator<(const Point2D &that) const {
			return ((x < that.x) || ((x == that.x) && (y < that.y)));
		};
		bool operator<=(const Point2D &that) const {
			return ((x < that.x) || ((x == that.x) && (y <= that.y)));
		};
		bool operator>(const Point2D &that) const {
			return ((x > that.x) || ((x == that.x) && (y > that.y)));
		};
		bool operator>=(const Point2D &that) const {
			return ((x > that.x) || ((x == that.x) && (y >= that.y)));
		};
		bool operator==(const Point2D &that) const {
			return ((x == that.x) && (y == that.y));
		};
		string to_string() const {
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
		}
	private:
		double x, y;
};

ostream &operator<<(ostream &os, const Point2D &P) {
	return os << P.to_string();
}

#endif