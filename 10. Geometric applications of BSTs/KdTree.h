/*
PointSET.h and KdTree.h should be derived class of some virtual Base class.
We should not be able to instantiate objects of Base class, only of the derived classes.
*/

#ifndef KD_TREE_H
#define KD_TREE_H

#include "BST.h"
#include "Point2D.h"
#include "RectHV.h"
#include <deque>

using std::deque;

class KdTree;

ostream &print(ostream &, const KdTree &);

class KdTree {
	friend ostream &print(ostream &, const KdTree &);
	public:
		KdTree(): tree(BST<Point2D, bool>()) {};
		bool isEmpty() const { return (tree.size() == 0); };
		size_t size() const { return tree.size(); };
		void insert(const Point2D &);
		bool contains(const Point2D &) const;
		deque<Point2D> range(const RectHV &) const;
		size_t range_count(const RectHV &) const;
		Point2D nearest(const Point2D &) const;
	private:
		// helper functions
		Node<Point2D, bool> *insert
			(const Point2D &, bool, Node<Point2D, bool> *);
		void range
			(const RectHV &, Node<Point2D, bool> *, deque<Point2D> &q) const;	
		void range_count
			(const RectHV &, Node<Point2D, bool> *, size_t &q) const;	
		void nearest(const Point2D &, Node<Point2D, bool> *, Point2D &N) const;

		// true value = order by x-coordinate;
		// false value = order by y-coordinate;
		BST<Point2D, bool> tree;
};

void KdTree::insert(const Point2D &P) {
	tree.root = insert(P, true, tree.root);	
}

bool KdTree::contains(const Point2D &P) const {
	Node<Point2D, bool> *node(tree.root);
	while (node) 
		if (node->val) {
			if (node->key.x_coord() < P.x_coord()) 
				node = node->right;
			else {
				if (node->key.x_coord() > P.x_coord()) 
					node = node->left;
				else 	
					return true;
			}
		} else {
			if (node->key.y_coord() < P.y_coord()) 
				node = node->right;
			else {
				if (node->key.y_coord() > P.y_coord()) 
					node = node->left;
				else 	
					return true;
			}
		}
	return false;
}

deque<Point2D> KdTree::range(const RectHV &R) const {
	deque<Point2D> q;
	range(R, tree.root, q);
	return q;
}

size_t KdTree::range_count(const RectHV &R) const {
	size_t k(0);
	range_count(R, tree.root, k);
	return k;
}

Point2D KdTree::nearest(const Point2D &P) const {
	if (isEmpty()) {
		cout << "Set is empty" << endl;
		return Point2D();
	}
	Point2D N(tree.root->key);
	nearest(P, tree.root, N);
	return N;
}

// helper functions
Node<Point2D, bool> *KdTree::insert
	(const Point2D &P, bool v, Node<Point2D, bool> *node) {
	if (node == nullptr) 
		return new Node<Point2D, bool>(P, v);
	if (v) {
		if (node->key.x_coord() > P.x_coord()) 
				node->left = insert(P, !v, node->left);
			 else 
				node->right = insert(P, !v, node->right);
	} else	{
		if (node->key.y_coord() > P.y_coord()) 
				node->left = insert(P, !v, node->left);
			 else
				node->right = insert(P, !v, node->right);
	}
	node->count = 1 + tree.size(node->left) + tree.size(node->right);	
	return node;			
}

void KdTree::range
	(const RectHV &R, Node<Point2D, bool> *node, deque<Point2D> &q) const {
	if (node == nullptr) return;
	if (node->val) {
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
	} else {
		if ((node->key).y_coord() < R.y_min()) 
			range(R, node->right, q);
		else 
			if ((node->key).y_coord() > R.y_max()) 
				range(R, node->left, q);
			else {
				range(R, node->left, q);
				if (R.contains(node->key))
					q.push_back(node->key);
				range(R, node->right, q);
			}		
	}		
}

void KdTree::range_count
	(const RectHV &R, Node<Point2D, bool> *node, size_t &k) const {
	if (node == nullptr) return;
	if (node->val) {
		if ((node->key).x_coord() < R.x_min()) 
			range_count(R, node->right, k);
		else 
			if ((node->key).x_coord() > R.x_max()) 
				range_count(R, node->left, k);
			else {
				range_count(R, node->left, k);
				if (R.contains(node->key))
					++k;
				range_count(R, node->right, k);
			}
	} else {
		if ((node->key).y_coord() < R.y_min()) 
			range_count(R, node->right, k);
		else 
			if ((node->key).y_coord() > R.y_max()) 
				range_count(R, node->left, k);
			else {
				range_count(R, node->left, k);
				if (R.contains(node->key))
					++k;
				range_count(R, node->right, k);
			}		
	}		
}

void KdTree::nearest
	(const Point2D &P, Node<Point2D, bool> *node, Point2D &N) const {
	if (node == nullptr) return;
	if (P.distanceTo(node->key) < P.distanceTo(N)) 		
		N = node->key;
	if (node->val) {
		if (node->key.x_coord() < P.x_coord()) {
			nearest(P, node->right, N);
			nearest(P, node->left, N);
		} else {
			nearest(P, node->left, N);
			nearest(P, node->right, N);
		}
	} else {
		if (node->key.y_coord() < P.y_coord()) {
			nearest(P, node->right, N);
			nearest(P, node->left, N);
		} else {
			nearest(P, node->left, N);
			nearest(P, node->right, N);
		}
	}	
}
		
// friend functions
ostream &print(ostream &os, const KdTree &A) {
	return print(os, A.tree);
}

#endif