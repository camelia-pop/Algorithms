#ifndef RED_BLACK_BST_NO_COLOR_H
#define RED_BLACK_BST_NO_COLOR_H

#include <iostream>
#include <ostream>

using std::cout;
using std::endl;
using std::ostream;
using std::size_t;

/**********************************
* 				Node
* (color bit is removed from Node)
**********************************/

template <typename Key, typename Value> class RBBST_no_color;

template <typename Key, typename Value> class Node;

template <typename Key, typename Value>
ostream &print(ostream &, const Node<Key, Value> * const);

template <typename Key, typename Value>
class Node {
	friend class RBBST_no_color<Key, Value>;
	friend ostream &print<>(ostream &, const Node * const);
	public:
		// c = false means black, c = true means red
		Node(const Key &k, const Value &v, bool c = false): 
			key(k), val(v), count(1) {
			if (c) { // red node
				left = null2;
				right = null1;
			} else { // black node
				left = null1;
				right = null2;
			}
		};	
		Key get_key() const { return key; };
		Value get_value() const { return val; };				
		size_t get_count() const { return count; };	
		bool isNull() const;	
		bool isRed() const;
		~Node() { };	
	private:
		// default constructor is made private because it is only used to define the static member null2; every node of RBBST is instantiated using the public constructor so we can keep track of its color
		Node(): left(nullptr), right(nullptr), count(0) {};
		
		static Node<Key, Value> *null1;
		static Node<Key, Value> *null2;	
	
		Key key;
		Value val;
		Node *left, *right;
		size_t count;	
};

template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::null1 = nullptr;

template <typename Key, typename Value>
Node<Key, Value> *Node<Key, Value>::null2 = new Node<Key, Value>();

template <typename Key, typename Value>		
inline bool Node<Key, Value>::isNull() const {
	if ((this == null1) || (this == null2))
		return true;
	return false;	
}

template <typename Key, typename Value>		
inline bool Node<Key, Value>::isRed() const {
	if (isNull())
		return false;
	if (left == null1)
		return false;
	if (left == null2)
		return true;
	return (key < left->key);		
}

// friend functions
template <typename Key, typename Value>		
ostream &print(ostream &os, const Node<Key, Value> * const node) {
	if (!node->isNull()) {
		if (node->isRed()) {
			print(os, node->right);
			os << "(" << node->get_key() << ", " << node->get_value() << "; red)\n";
			print(os, node->left);			
		} else {
			print(os, node->left);
			os << "(" << node->get_key() << ", " << node->get_value() << "; black)\n";
			print(os, node->right);
		}
	}
	return os;
}

/**********************************************
*         Red-Black Binary Search Tree 
*(left-leaning without extra memory for color;
* a node is colored red if their children are swapped,
* i.e., the left child > red child)
**********************************************/
template <typename Key, typename Value> class RBBST_no_color;

template <typename Key, typename Value>
ostream &print(ostream &, const RBBST_no_color<Key, Value> &);

template <typename Key, typename Value>
class RBBST_no_color {
	friend ostream &print<>(ostream &, const RBBST_no_color &);
	public:
		RBBST_no_color(): root(Node<Key, Value>::null1) {};
		void insert(const Key &k, const Value &v);
		size_t size() const;
		size_t depth() const;
		~RBBST_no_color();
	private:
		// helper functions
		Node<Key, Value> *insert(const Key &, const Value &, Node<Key, Value> *);
		bool isRed(Node<Key, Value> *) const;
		Node<Key, Value> *rotateLeft1(Node<Key, Value> *);
		Node<Key, Value> *rotateLeft2(Node<Key, Value> *);
		Node<Key, Value> *rotateRight(Node<Key, Value> *);
		void flipChildren(Node<Key, Value> *);
		void flipColors(Node<Key, Value> *);
		size_t size(const Node<Key, Value> * const) const;
		void depth(const Node<Key, Value> * const, size_t , size_t &) const;
		void deleteTree(Node<Key, Value> *);		
		// data member
		Node<Key, Value> *root;
};

template <typename Key, typename Value>
void RBBST_no_color<Key, Value>::insert(const Key &k, const Value &v) {
	root = insert(k, v, root);
	// need to update the color of the root, because it may have been flipped to red, but the root should always be black	
	if (root->isRed())
		flipChildren(root);	
}

template <typename Key, typename Value>
size_t RBBST_no_color<Key, Value>::size() const {
	return size(root);
}

template <typename Key, typename Value>
size_t RBBST_no_color<Key, Value>::depth() const {
	size_t d_max = 0;
	depth(root, 0, d_max);
	return d_max;
}

template <typename Key, typename Value>
RBBST_no_color<Key, Value>::~RBBST_no_color() {
	deleteTree(root);
}

// helper functions
template <typename Key, typename Value>
Node<Key, Value> *RBBST_no_color<Key, Value>::insert
	(const Key &k, const Value &v, Node<Key, Value> *node) {	
    if (node->isNull())
		return (node == root) 
	            ? new Node<Key, Value>(k, v, false)
			    : new Node<Key, Value>(k, v, true);
	if (node->isRed()) {
		if (node->key == k) 
			node->val = v;
		else if (node->key > k) 
				node->right = insert(k, v, node->right);
			 else
				node->left = insert(k, v, node->left);					
	} else {
		if (node->key == k) 
			node->val = v;
		else if (node->key > k) 
				node->left = insert(k, v, node->left);
			 else
				node->right = insert(k, v, node->right);				
	}
	
	// update count
	node->count = 1 + size(node->left) + size(node->right);	
	
	// check if rotateLeft is needed
	if ((!node->isRed()) && (!node->left->isRed()) 
		 && node->right->isRed()) 
		node = rotateLeft1(node);
		
	if (node->isRed() && node->left->isRed() 
		 && (!node->right->isRed())) 
		node = rotateLeft2(node);
		
	// check if rotateRight is needed
	if ((!node->isRed()) && node->left->isRed() && node->left->right 
		 && node->left->right->isRed()) 
		node = rotateRight(node);
	
	// check if color needs to be flipped: both children are red
	if (node->left->isRed() && node->right->isRed()) 
		flipColors(node);
	
	return node;
}

template <typename Key, typename Value>
Node<Key, Value> *RBBST_no_color<Key, Value>::rotateLeft1
	(Node<Key, Value> *node) {
	/* assumption: 
		(node is black, node->left is black, node->right is red)
	*/
	Node<Key, Value> *temp(node->right);
	node->right = node->left;
	node->left = temp->right;
	temp->right = temp->left;
	temp->left = node;
	if (node->left == Node<Key, Value>::null1) 
		node->left = Node<Key, Value>::null2;	
	// update counts
	node->count = 1 + size(node->left) + size(node->right);
	temp->count = 1 + size(temp->left) + size(temp->right);
	return temp;
}

template <typename Key, typename Value>
Node<Key, Value> *RBBST_no_color<Key, Value>::rotateLeft2
	(Node<Key, Value> *node) {
	/* assumption: 
		(node is red, node->left is red, node->right is black)
	*/
	Node<Key, Value> *temp(node->left);
	node->left = temp->right;
	temp->right = node;
	if (node->left == Node<Key, Value>::null1) 
		node->left = Node<Key, Value>::null2;	
	// update counts
	node->count = 1 + size(node->left) + size(node->right);
	temp->count = 1 + size(temp->left) + size(temp->right);
	return temp;
}

template <typename Key, typename Value>
Node<Key, Value> *RBBST_no_color<Key, Value>::rotateRight
	(Node<Key, Value> *node){
	/*	assumption: 
		(node is black, node->left is red, and node->left->right is red)
	*/	
	Node<Key, Value> *temp(node->left);
	node->left =  node->right;
	node->right = temp->left;
	if (node->left == Node<Key, Value>::null1)
		node->left = Node<Key, Value>::null2;
	if (node->right == Node<Key, Value>::null2)
		node->right = Node<Key, Value>::null1;
	temp->left = temp->right;
	temp->right = node;	
	// update counts
	node->count = 1 + size(node->left) + size(node->right);
	temp->count = 1 + size(temp->left) + size(temp->right);		
	return temp;	
}

template <typename Key, typename Value>
void RBBST_no_color<Key, Value>::flipChildren(Node<Key, Value> *node){
	Node<Key, Value> *temp(node->left);
	node->left = node->right;
	node->right = temp;
}

template <typename Key, typename Value>
void RBBST_no_color<Key, Value>::flipColors(Node<Key, Value> *node){
	// assumption: both children are red
	flipChildren(node);
	flipChildren(node->left);
	flipChildren(node->right);
}

template <typename Key, typename Value>
inline size_t RBBST_no_color<Key, Value>::size
	(const Node<Key, Value> * const node) const{
	return (!node->isNull()) ? node->count : 0;	
}

template <typename Key, typename Value>
void RBBST_no_color<Key, Value>::depth
	(const Node<Key, Value> * const node, size_t d, size_t &d_max) const {
	if (node->isNull())
		return;	
	if (node->left->isNull() && node->right->isNull()) {
		if (d > d_max)
			d_max = d;	
	} else {
		depth(node->left, d + 1, d_max);
		depth(node->right, d + 1, d_max);
	}
}

template <typename Key, typename Value>
void RBBST_no_color<Key, Value>::deleteTree(Node<Key, Value> *node) {
	if (!node->isNull()) {
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

// friend functions
template <typename Key, typename Value>
ostream &print(ostream &os, const RBBST_no_color<Key, Value> &tree) {
	return print(os, tree.root);
}

#endif