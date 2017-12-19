#include "BST.h"
#include "Point2D.h"
#include "PointSET.h"
#include <iostream>

using std::cout;
using std::endl;

// template specialization
template <>		
ostream &print<Point2D, bool>(ostream &os, const Node<Point2D, bool> * const node) {
	if (node) {
		print(os, node->left);
		os << node->key << endl;
		print(os, node->right);
	}
	return os;
}

int main() {
	PointSET A;
	A.insert(Point2D(0.5, 0.5));
	A.insert(Point2D(0.25, 0.25));
	A.insert(Point2D(0.25, 0.75));
	A.insert(Point2D(0.75, 0.25));
	A.insert(Point2D(0.75, 0.75));
	
	cout << "Set A: " << endl;
	print(cout, A) << endl;
	cout << "A is empty? " << A.isEmpty() << endl;
	cout << "A contains " << Point2D(0.5, 0.5) << "? " << A.contains(Point2D(0.5, 0.5)) << endl;
	cout << "A contains " << Point2D(0.5, 0.6) << "? " <<  A.contains(Point2D(0.5, 0.6)) << endl;
		
	RectHV R(0.0, 0.0, 0.5, 0.5);
	cout << "Rectangle R: " << R.to_string() << endl;
	cout << "A intersected with R: " << endl;
	deque<Point2D> q(A.range(R));
	for (auto it = q.begin(); it != q.end(); ++it)
		cout << it->to_string() << endl;
	
	cout << endl;
	Point2D Q(A.nearest(Point2D(0.1, 0.1)));
	cout << "Nearest point in A to " << Point2D(0.1, 0.1) << ": " << Q << endl;
}
