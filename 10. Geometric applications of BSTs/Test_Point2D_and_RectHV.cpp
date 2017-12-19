#include "Point2D.h"
#include "RectHV.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	Point2D P(0.2, 0.3), Q(0.15, 0.5), S(1.2, 3.0);
	cout << "P coordinates: " << P.x_coord() << " " << P.y_coord() << endl;
	cout << "P " << P << endl;
	cout << "Q " << Q.to_string() << endl;
	cout << "(P < Q)? " << (P < Q) << endl;
	cout << "(P > Q)? " << (P > Q) << endl;
	cout << "(P == Q)? " << (P == Q) << endl;
	cout << "Distance P to Q = " << P.distanceTo(Q) << endl;
	cout << "Distance P to Q squared = " <<  P.distanceSquaredTo(Q) << endl;
	cout << endl << endl;
	
	RectHV R1(0.1, 0.1, 0.2, 0.3), R2(0.15, 0.15, 0.3, 0.4),
		   R3(0.5, 0.5, 0.6, 0.6);
	cout << "Rectangle R1: " << R1.to_string() << endl;
	cout << "Rectangle R2: " << R2.to_string() << endl;
	cout << "Rectangle R3: " << R3.to_string() << endl;
	cout << "R2 contains Q? " << R2.contains(Q) << endl;
	cout << "R1 intersects R2? " << R1.intersects(R2) << endl;
	cout << "R1 intersects R3? " << R1.intersects(R3) << endl;
	cout << "Distance from R1 to Q squared = " << R1.distanceSquaredTo(Q) << endl;
	cout << "(R1 == R2)? " << (R1 == R2) << endl;
}