#ifndef POINT_H
#define POINT_H

#include <limits>
#include <string>

using std::numeric_limits;
using std::string;
using std::to_string;

class Point;

bool comparePoint(const Point&, const Point&);
bool compareSlope(const Point&, const Point&, const Point&);

class Point {
	public:
		Point(double x0 = 0.0, double y0 = 0.0): x(x0), y(y0) {};
		// void draw();
		// void drawTo(Point that);
		bool operator==(const Point &that) const {
			return ((x == that.x) && (y == that.y));
		};
		bool operator!=(const Point &that) const {
			return (! this->operator==(that));			
		};
		double slopeTo(const Point &that) const {
			if ((x == that.x) && (y == that.y)) 
				return (-1.0) * numeric_limits<double>::max();
			if (x == that.x) 
				return numeric_limits<double>::max();
			return (y - that.y) / (x - that.x);							
		};
		bool compareTo(const Point &that) const {
			if ((y < that.y) || ((y == that.y) && (x < that.x))) 
				return true;
			return false;
		}
		/*
		* Compares two points by the slope they make with this point.
		* The slope is defined as in the slopeTo() method.
		*/
		bool slopeOrder(const Point &P, const Point &Q) const {
			return this->slopeTo(P) < this->slopeTo(Q);
		}
		string toString() const {
            return "(" + to_string(x) + ", " + to_string(y) + ")";
		};
	private:
		double x;
		double y;
};

#endif