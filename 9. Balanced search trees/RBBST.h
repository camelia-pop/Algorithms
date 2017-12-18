#ifndef RED_BLACK_BST_H
#define RED_BLACK_BST_H

#include <exception>
#include <iostream>
#include <ostream>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::runtime_error;
using std::size_t;
using std::vector;


/**********************************
* 			NodeRB
**********************************/

template <typename Key, typename Value> class RBBST;

template <typename Key, typename Value> class NodeRB;

template <typename Key, typename Value>
ostream &print(ostream &, const NodeRB<Key, Value> * const);

template <typename Key, typename Value>
class NodeRB {
	friend class RBBST<Key, Value>;
	friend ostream &print<>(ostream &, const NodeRB * const);
	public:
		NodeRB(bool c = true): 
			left(nullptr), right(nullptr), count(0), color(c) {};
		NodeRB(const Key &k, const Value &v, bool c = true): 
			key(k), val(v), left(nullptr), right(nullptr), count(1), color(c) {};
		bool isRed() { return color; };	
		Key get_key() const { return key; };
		Value get_value() const { return val; };
		bool get_color() const { return color; };				
		size_t get_count() const { return count; };		
		~NodeRB() { left = right = nullptr; };	
	private:
		Key key;
		Value val;
		bool color; // true = red, false = black
		NodeRB *left, *right;
		size_t count;	
};

// friend functions
template <typename Key, typename Value>		
ostream &print(ostream &os, const NodeRB<Key, Value> * const NodeRB) {
	if (NodeRB) {
		print(os, NodeRB->left);
		os << "(" << NodeRB->get_key() << ", " << NodeRB->get_value() << "; ";
		if (NodeRB->get_color())
			cout << "red)" << endl;
		else
			cout << "black)" << endl;
		print(os, NodeRB->right);
	}
	return os;
}

/**********************************************
*         Red-Black Binary Search Tree 
*
**********************************************/
template <typename Key, typename Value> class RBBST;

template <typename Key, typename Value>
ostream &print(ostream &, const RBBST<Key, Value> &);

template <typename Key, typename Value>
class RBBST {
	friend ostream &print<>(ostream &, const RBBST &);
	public:
		RBBST(): root(nullptr) {};
		void insert(const Key &k, const Value &v);
		size_t size() const;
		size_t depth() const;
		~RBBST();
	private:
		// helper functions
		NodeRB<Key, Value> *insert(const Key &, const Value &, NodeRB<Key, Value> *);
		bool isRed(const NodeRB<Key, Value> * const) const;
		NodeRB<Key, Value> *rotateLeft(NodeRB<Key, Value> *);
		NodeRB<Key, Value> *rotateRight(NodeRB<Key, Value> *);
		void flipColors(NodeRB<Key, Value> *);
		size_t size(const NodeRB<Key, Value> * const) const;
		void depth(const NodeRB<Key, Value> * const, size_t, size_t &) const;
		void deleteTree(NodeRB<Key, Value> *);		
		// data member
		NodeRB<Key, Value> *root;
};

template <typename Key, typename Value>
void RBBST<Key, Value>::insert(const Key &k, const Value &v) {
	root = insert(k, v, root);
	root->color = false;	
}

template <typename Key, typename Value>
size_t RBBST<Key, Value>::size() const {
	return size(root);
}

template <typename Key, typename Value>
size_t RBBST<Key, Value>::depth() const {
	size_t d_max = 0;
	depth(root, 0, d_max);
	return d_max;
}

template <typename Key, typename Value>
RBBST<Key, Value>::~RBBST() {
	deleteTree(root);
}

// helper functions
template <typename Key, typename Value>
NodeRB<Key, Value> *RBBST<Key, Value>::insert
	(const Key &k, const Value &v, NodeRB<Key, Value> *node) {	
    if (node) {
		if (node->key == k) 
			node->val = v;
		else if (node->key > k) 
				node->left = insert(k, v, node->left);
			 else
				node->right = insert(k, v, node->right);				
	} else 
		if (root)
			return new NodeRB<Key, Value>(k, v);
		else 
			return new NodeRB<Key, Value>(k, v, false);
	
	// update count
	node->count = 1 + size(node->left) + size(node->right);	
	
	// check if rotateLeft is needed: left = black, right = red
	if ((!isRed(node->left)) && isRed(node->right))
		node = rotateLeft(node);
	// check if rotateRight is needed: left = red, left->left = red (two consecutive reds)
	if (isRed(node->left) && node->left->left && isRed(node->left->left))
		node = rotateRight(node);
	// check is color needs to be flipped: both children are red
	if (isRed(node->left) && isRed(node->right))
		flipColors(node);
	
	return node;
}

template <typename Key, typename Value>
bool RBBST<Key, Value>::isRed(const NodeRB<Key, Value> * const node) const {
	return (node == nullptr) ? false : node->color;
}

template <typename Key, typename Value>
NodeRB<Key, Value> *RBBST<Key, Value>::rotateLeft(NodeRB<Key, Value> *node) {
	// assumption: the right child of node is red
	
	NodeRB<Key, Value> *temp(node->right);
	// update links
	node->right = temp->left;
	temp->left = node;
	// update colors
	temp->color = node->color;
	node->color = true;
	// update counts
	node->count = 1 + size(node->left) + size(node->right);
	temp->count = 1 + size(temp->left) + size(temp->right);
	return temp;
}

template <typename Key, typename Value>
NodeRB<Key, Value> *RBBST<Key, Value>::rotateRight(NodeRB<Key, Value> *node){
	// assumption: the left child of node is red
	
	NodeRB<Key, Value> *temp(node->left);
	// update links
	node->left = temp->right;
	temp->right = node;
	// update colors
	temp->color = node->color;
	node->color = true;
	// update counts
	node->count = 1 + size(node->left) + size(node->right);
	temp->count = 1 + size(temp->left) + size(temp->right);
	return temp;
}

template <typename Key, typename Value>
void RBBST<Key, Value>::flipColors(NodeRB<Key, Value> *node){
	// assumption: node is black and both children are red
	node->color = true;
	node->left->color = false;
	node->right->color = false;

}
template <typename Key, typename Value>
size_t RBBST<Key, Value>::size(const NodeRB<Key, Value> * const node) const{
	return (node) ? node->count : 0;	
}

template <typename Key, typename Value>
void RBBST<Key, Value>::depth
	(const NodeRB<Key, Value> * const node, size_t d, size_t &d_max) const {
	if (node == nullptr)
		return;	
	if ((node->left == nullptr) && (node->right == nullptr)) {
		if (d > d_max)
			d_max = d;	
	} else {
		depth(node->left, d + 1, d_max);
		depth(node->right, d + 1, d_max);
	}
}

template <typename Key, typename Value>
void RBBST<Key, Value>::deleteTree(NodeRB<Key, Value> *node) {
	if (node) {
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

// friend functions
template <typename Key, typename Value>
ostream &print(ostream &os, const RBBST<Key, Value> &tree) {
	return print(os, tree.root);
}

#endif