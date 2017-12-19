#ifndef BST_H
#define BST_H

#include <deque>
#include <exception>
#include <iostream>
#include <ostream>
#include <stack>
#include <vector>

using std::cout;
using std::deque;
using std::endl;
using std::ostream;
using std::runtime_error;
using std::size_t;
using std::stack;
using std::vector;

template <typename Key, typename Value> class BST;

template <typename Key, typename Value> class Node;

template <typename Key, typename Value>
ostream &print(ostream &, const Node<Key, Value> * const);

/**********************************
* 				Node
**********************************/
template <typename Key, typename Value>
class Node {
	friend class PointSET;
	friend class KdTree;
	friend class BST<Key, Value>;
	friend ostream &print<>(ostream &, const Node * const);
	public:		
		Node(): left(nullptr), right(nullptr), count(0) {};
		Node(const Key &k, const Value &v): 
			key(k), val(v), left(nullptr), right(nullptr), count(1) {};
		Key get_key() const { return key; };
		Value get_value() const { return val; };		
		~Node() { left = right = nullptr; };	
	private:
		Key key;
		Value val;
		Node *left, *right;
		// number of nodes in the subtree rooted at the current node
		size_t count;	
};

// friend functions
template <typename Key, typename Value>		
ostream &print(ostream &os, const Node<Key, Value> * const node) {
	if (node) {
		print(os, node->left);
		os << "(" << node->key << ", " << node->val << ") ";
		print(os, node->right);
	}
	return os;
}

/**********************************
* 		Binary search tree
**********************************/
// display elements of BST inorder		
template <typename Key, typename Value>
ostream &print(ostream &, const BST<Key, Value> &);

template <typename Key, typename Value>
class BST {
	friend ostream &print<>(ostream &, const BST &);
	friend class PointSET;
	friend class KdTree;
	public:
		BST(): root(nullptr) {};
		void insert(const Key &, const Value &);
		void deleteMin();
		void deleteMax();
		// Hibbard deletion
		void deleteNode(const Key &);
		const Node<Key, Value> *min() const;
		const Node<Key, Value> *max() const;
		size_t size() const;
		size_t depth() const;
		// return -1 if key is not found in the tree
		int rank(const Key &) const;
		bool find(const Key &) const;
		size_t range_count(const Key &, const Key &) const;
		deque<Node<Key, Value>> range_search(const Key &, const Key &) const;
		// return value associated to a key
		const Value &get(const Key &) const;
		Value &get(const Key &);
		// return the key smaller but closest to a given key
		Key floor(const Key &) const;
		// return the key larger but closest to a given key
		Key ceiling(const Key &) const;
		// inorder traversal using constant extra space -- Morris method
		// time O(n), extra space O(1)
		void morrisTraversal() const;
		// inorder traversal with stack, non-recursive 
		// time O(n), extra space O(log n) on average
		void stackTraversal() const;
		~BST();
	private:
		// helper functions
		Node<Key, Value> *insert(const Key &, const Value &, Node<Key, Value> *);
		Node<Key, Value> *deleteMin(Node<Key, Value> *);
		Node<Key, Value> *deleteMax(Node<Key, Value> *);
		Node<Key, Value> *deleteNode(const Key &, Node<Key, Value> *);
		const Node<Key, Value> *min(Node<Key, Value> *) const;
		const Node<Key, Value> *max(Node<Key, Value> *) const;
		size_t size(const Node<Key, Value> * const) const;
		void depth(const Node<Key, Value> * const, size_t, size_t &) const;
		Node<Key, Value> *predecessor(Node<Key, Value> *) const;
		void range_search
		(const Key &, const Key &, Node<Key, Value> *, deque<Node<Key, Value>> &) const;
		void deleteTree(Node<Key, Value> *);
		// data member
		Node<Key, Value> *root;
};

template <typename Key, typename Value>
void BST<Key, Value>::insert(const Key &k, const Value &v) {
	root = insert(k, v, root);		
}

template <typename Key, typename Value>
void BST<Key, Value>::deleteMin() {
	root = deleteMin(root);		
}

template <typename Key, typename Value>
void BST<Key, Value>::deleteMax() {
	root = deleteMax(root);		
}

template <typename Key, typename Value>
void BST<Key, Value>::deleteNode(const Key &k) {
	root = deleteNode(k, root);
}

template <typename Key, typename Value>
const Node<Key, Value> *BST<Key, Value>::min() const {
	return min(root);
}

template <typename Key, typename Value>
const Node<Key, Value> *BST<Key, Value>::max() const {
	return max(root);
}

template <typename Key, typename Value>
size_t BST<Key, Value>::size() const {
	return size(root);
}

template <typename Key, typename Value>
size_t BST<Key, Value>::depth() const {
	size_t d_max = 0;
	depth(root, 0, d_max);
	return d_max;
}

template <typename Key, typename Value>
int BST<Key, Value>::rank(const Key &k) const {
	size_t c = 0;
	bool found = false;
	Node<Key, Value> *node(root);
	while (node) {
		if (node->key < k) {
			c += 1 + size(node->left);
			node = node->right;
		} else if (node->key > k) 
				   node = node->left;
			   else {
				   found = true;
				   c += size(node->left);
				   break;
			   }
	}
	return found ? c : -1;
}

template <typename Key, typename Value>
bool BST<Key, Value>::find(const Key &k) const {
	Node<Key, Value> *node(root);
	while (node) 
		if (node->key < k) 
			node = node->right;
		else if (node->key > k) 
				node = node->left;
			 else 
				 return true;
	return false;
}

template <typename Key, typename Value>
size_t BST<Key, Value>::range_count(const Key &k1, const Key &k2) const {
	return (find(k2)) ? rank(k2) - rank(k1) + 1 : rank(k2) - rank(k1);
}

template <typename Key, typename Value>
deque<Node<Key, Value>> BST<Key, Value>::range_search
	(const Key &k1, const Key &k2) const {
	deque<Node<Key, Value>> q;
	range_search(k1, k2, root, q);
	return q;
}

template <typename Key, typename Value>
const Value &BST<Key, Value>::get(const Key &k) const {
	Node<Key, Value> *node(root);
	while (node) 
		if (node->key < k) 
			node = node->right;
		else if (node->key > k) 
				node = node->left;
			 else 
				 return node->val;
	if (!node) {
		cout << "Key not found in tree!" << endl;
		throw runtime_error("Key not found in BST\n");
	}
}

template <typename Key, typename Value>
Value &BST<Key, Value>::get(const Key &k) {
	Node<Key, Value> *node(root);
	while (node) 
		if (node->key < k) 
			node = node->right;
		else if (node->key > k) 
				node = node->left;
			 else 
				 return node->val;
	if (!node) {
		cout << "Key not found in tree!" << endl;
		throw runtime_error("Key not found in BST\n");
	}
}

template <typename Key, typename Value>
Key BST<Key, Value>::floor(const Key &k) const {
	Node<Key, Value> *node(root);
	while (node) {
		if (node->key == k) 
			return node->key;
		else if (node->key > k) 
				node = node->left;
			 else {
				 if (node->right) {
				   if (node->right->key <= k)
					   node = node->right;
				   else {
				       const Node<Key, Value> *t(min(node->right));
				       if (t) {
					      if (t->key > k)
						      return node->key;		
					      else if (t->key == k)
							       return k;
						       else if (t->key > node->key)
								        node = node->right;
                                    else 
								        return node->key;
                       } else 
					         return node->key;		
			       }
				 } else
                       return node->key;					 
		     }	
	}	
	if (!node) {
		cout << "There is no key in BST smaller than the given key!" << endl;
		throw runtime_error("There is no key in BST smaller than the given key\n");
	}
}

template <typename Key, typename Value>
Key BST<Key, Value>::ceiling(const Key &k) const {
	Node<Key, Value> *node(root);
	while (node) {
		if (node->key == k) 
			return node->key;
		else if (node->key < k) 
				node = node->right;
			 else {
				 if (node->left) {
				   if (node->left->key >= k)
					   node = node->left;
				   else {
				       const Node<Key, Value> *t(max(node->left));
				       if (t) {
					      if (t->key < k)
						      return node->key;		
					      else if (t->key == k)
							       return k;
						       else if (t->key < node->key)
								        node = node->left;
                                    else 
								        return node->key;
                       } else 
					         return node->key;		
			       }
				 } else
                       return node->key;					 
		     }			 
	}
	if (!node) {
		cout << "There is no key in BST larger than the given key!" << endl;
		throw runtime_error("There is no key in BST larger than the given key\n");
	}
}

template <typename Key, typename Value>
void BST<Key, Value>::morrisTraversal() const {
	Node<Key, Value> *node(root), *pred;
	while (node) {
		if (node->left) {
			// find the predecessor of node
			pred = predecessor(node);
			if (pred->right == nullptr) {
				// make node the right child of pred to know where to return when we arrive at pred
				pred->right = node;
				// continue to the left child of node
				node = node->left;
			} else {
				// revert the changes made
				pred->right = nullptr;
				// print the current node
				cout << "(" << node->key << ", " << node->val << ") ";
				// continue to the right child of node
				node = node->right;
			}
		} else {
			cout << "(" << node->key << ", " << node->val << ") ";
			node = node->right;
		}
	}
}

template <typename Key, typename Value>
void BST<Key, Value>::stackTraversal() const {
	Node<Key, Value> *node(root);
	stack<Node<Key, Value>*> st;
	while ((node) || (!st.empty())) {
		if (node) {
			st.push(node);
			node = node->left;
		} else {
			node = st.top();
			st.pop();
			cout << "(" << node->key << ", " << node->val << ") ";
			node = node->right;
		}
	}
}

template <typename Key, typename Value>
BST<Key, Value>::~BST() {
	deleteTree(root);
}

// helper functions
template <typename Key, typename Value>
Node<Key, Value> *BST<Key, Value>::insert
	(const Key &k, const Value &v, Node<Key, Value> *node) {	
    if (node) {
		if (node->key == k) 
			node->val = v;
		else if (node->key > k) 
				node->left = insert(k, v, node->left);
			 else
				node->right = insert(k, v, node->right);				
	} else
		node = new Node<Key, Value>(k, v);
	node->count = 1 + size(node->left) + size(node->right);	
	return node;
}

template <typename Key, typename Value>
Node<Key, Value> *BST<Key, Value>::deleteMin(Node<Key, Value> *node) {
	if (!node) 
		return nullptr;
	if (node->left)
		node->left = deleteMin(node->left);
	else {
		Node<Key, Value> *temp = node;
		node = node->right;		
		delete temp;
	}
	if (node)
		node->count = 1 + size(node->left) + size(node->right);	
	return node;
}

template <typename Key, typename Value>
Node<Key, Value> *BST<Key, Value>::deleteMax(Node<Key, Value> *node) {
	if (!node) 
		return nullptr;
	if (node->right)
		node->right = deleteMax(node->right);
	else {
		Node<Key, Value> *temp = node;
		node = node->left;		
		delete temp;
	}
	if (node)
		node->count = 1 + size(node->left) + size(node->right);	
	return node;
}

template <typename Key, typename Value>
Node<Key, Value> *BST<Key, Value>::deleteNode
	(const Key &k, Node<Key, Value> *node) {
	if (!node) 
		return nullptr;
	if (node->key > k)
		node->left = deleteNode(k, node->left);
	else 
		if (node->key < k)
			node->right = deleteNode(k, node->right);
		else 
			if (!node->left) {
				Node<Key, Value> *temp = node;
				node = temp->right;
				delete temp;
		    } else 
				if (!node->right) {
					Node<Key, Value> *temp = node;
					node = temp->left;
					delete temp;
			    } else {
					const Node<Key, Value> *temp = min(node->right);
					node->key = temp->key;
					node->val = temp->val;
					node->right = deleteMin(node->right);			
				}
	if (node)
		node->count = 1 + size(node->left) + size(node->right);	
	return node;
}

template <typename Key, typename Value>
const Node<Key, Value> *BST<Key, Value>::min(Node<Key, Value> *node) const {	
	if (node)
		if (node->left)
			return min(node->left);
		else
			return node;
	else
		return nullptr;	
}

template <typename Key, typename Value>
const Node<Key, Value> *BST<Key, Value>::max(Node<Key, Value> *node) const {	
	if (node)
		if (node->right)
			return max(node->right);
		else
			return node;
	else
		return nullptr;	
}

template <typename Key, typename Value>
size_t BST<Key, Value>::size(const Node<Key, Value> * const node) const{
	return (node) ? node->count : 0;	
}

template <typename Key, typename Value>
void BST<Key, Value>::depth
	(const Node<Key, Value> * const node, size_t d, size_t &d_max) const {
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
Node<Key, Value> *BST<Key, Value>::predecessor(Node<Key, Value> *node) const {
	// node->left != nullptr	
	Node<Key, Value> *temp(node->left);
	while ((temp->right) && (temp->right != node))	
		temp = temp->right;
	return temp;
}

template <typename Key, typename Value>
void BST<Key, Value>::range_search
	(const Key &k1, const Key &k2, Node<Key, Value> *node, 
	deque<Node<Key, Value>> &q) const {
	if (node == nullptr) return;
	if ((node->key >= k1) && (node->key <= k2)) {
		range_search(k1, k2, node->left, q);
		q.push_back(*node);
		range_search(k1, k2, node->right, q);
	} else if (node->key < k1)
				range_search(k1, k2, node->right, q);
		   else
				range_search(k1, k2, node->left, q);
}

template <typename Key, typename Value>
void BST<Key, Value>::deleteTree(Node<Key, Value> *node) {
	if (node) {
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

// friend function
template <typename Key, typename Value>
ostream &print(ostream &os, const BST<Key, Value> &tree) {
	return print(os, tree.root);
}

#endif