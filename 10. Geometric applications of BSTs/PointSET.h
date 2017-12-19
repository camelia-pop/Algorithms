/*
PointSET.h and KdTree.h should be derived class of some virtual Base class.
We should not be able to instantiate objects of Base class, only of the derived classes.
*/

#ifndef POINT_SET_H
#define POINT_SET_H

#include "BST.h"
#include "Point2D.h"
#include "RectHV.h"
#include <deque>

using std::deque;

class PointSET;

ostream &print(ostream &, const PointSET &);

class PointSET {
	friend ostream &print(ostream &, const PointSET &);
	public:		
		PointSET(): tree(BST<Point2D, bool>()) {};
		bool isEmpty() const { return (tree.size() == 0); };
		size_t size() const { return tree.size(); };
		void insert(const Point2D &P) { tree.insert(P, true); };
		bool contains(const Point2D &P) const { return tree.find(P); };
		deque<Point2D> range(const RectHV &) const;
		Point2D nearest(const Point2D &) const;
	private:
		// helper functions
		void range(const RectHV &, Node<Point2D, bool> *, 
				   deque<Point2D> &q) const;
		void nearest(const Point2D &, Node<Point2D, bool> *, Point2D &N) const;
		
		// data member
		// 1. the set of points is implemented as a BST -- can be replaced by a Red-Black BST for better complexity;
		// 2. type Value is bool because it is not used in any way and it occupies the smallest amount of memory;
		// 3. the comparison of the keys uses the comparison in Point2D, which is lexicografic order.		
		BST<Point2D, bool> tree;
};

deque<Point2D> PointSET::range(const RectHV &R) const {
	deque<Point2D> q;
	range(R, tree.root, q);	
	return q;
}

Point2D PointSET::nearest(const Point2D &P) const {
	if (isEmpty()) {
		cout << "Set is empty" << endl;
		return Point2D();
	}
	Point2D N(tree.root->key);
	nearest(P, tree.root, N);
	return N;
}

// helper functions
void PointSET::range(const RectHV &R, Node<Point2D, bool> *node, 
					 deque<Point2D> &q) const {
	if (node == nullptr) return;
	if ((node->key).x_coord() < R.x_min()) 
		range(R, node->right, q);
	else 
		if ((node->key).x_coord() > R.x_max()) 
			range(R, node->left, q);
		else {
			range(R, node->left, q);
			if (R.contains(node->key))
				q.push_back(node->key);
			range(R, node->right, q);
		}			
}

void PointSET::nearest(const Point2D &P, Node<Point2D, bool> *node,			              Point2D &N) const {
	if (node == nullptr) return;
	if (P.distanceTo(node->key) < P.distanceTo(N)) 		
		N = node->key;
	if (P < node->key) {
		nearest(P, node->left, N);
		nearest(P, node->right, N);
	} else {
		nearest(P, node->right, N);
		nearest(P, node->left, N);
	}
}

// friend functions
ostream &print(ostream &os, const PointSET &A) {
	return print(os, A.tree);
}

#endif