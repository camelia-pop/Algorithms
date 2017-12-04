/* 
Doubly-linked list
*/

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <utility>

using std::ostream;

template <typename T> struct Node {
	Node(): succ(nullptr), pred(nullptr) {};
	Node(const T &t): val(t), succ(nullptr), pred(nullptr) {};	
	template <typename... Args> 
	Node(Args&&... args):
		val(T(std::forward<Args>(args)...)), 
		succ(nullptr), pred(nullptr) { };
	~Node() { succ = pred = nullptr; };		
		
	T val;
	Node *succ, *pred;
};

template <typename T> class List;

template <typename T> ostream &print(ostream &, const List<T> &); 

template <typename T> class List_iterator;

template <typename T> class List_iterator {
	friend class List<T>;
	public:
		T &operator*() { return curr_node->val; };
		List_iterator &operator++() { 
			if (curr_node)
				curr_node = curr_node->succ;
			return *this;
		};
		List_iterator &operator--() { 
			if (curr_node)
				curr_node = curr_node->pred;
			return *this;
		};
		bool operator==(const List_iterator &li) { 
			return curr_node == li.curr_node;
		};
		bool operator!=(const List_iterator &li) { 
			return curr_node != li.curr_node;
		};
	private:
		List_iterator(Node<T> *n): curr_node(n) {};
		
		Node<T> *curr_node;
};

template <typename T> class List {
	friend ostream &print<T>(ostream &, const List<T> &); 	
	public:
		typedef List_iterator<T> iterator;
		
		List(): first(nullptr), last(nullptr), ctr(0) {};
		void push_back(const T &);
		void push_front(const T &);
		void pop_back();
		void pop_front();
		bool isEmpty() const { return ctr == 0; };
		size_t size() const { return ctr; };
		iterator begin() { return List_iterator<T>(first); };
		iterator end() { return List_iterator<T>(last); };
		~List();
	private:
		Node<T> *first, *last;
		// cache the size of the list
		size_t ctr;
};

template <typename T> 
void List<T>::push_back(const T &t) {
	++ctr;
	if (first == last) {
		first = new Node<T>(t);
		last = new Node<T>();
		first->succ = last;
		last->pred = first;
	} else {
		Node<T> *temp = new Node<T>();
		last->val = t;
		last->succ = temp;
		temp->pred = last;
		last = temp;
	}
}

template <typename T> 
void List<T>::push_front(const T &t) {
	++ctr;
	if (first == last) {
		first = new Node<T>(t);
		last = new Node<T>();
		first->succ = last;
		last->pred = first;
	} else {
		Node<T> *temp = new Node<T>(t);
		temp->succ = first;
		first->pred = temp;
		first = temp;
	}
}

template <typename T> 
void List<T>::pop_back() {
	if (first != last) {
		--ctr;
		Node<T> *temp = last;
		last = temp->pred;
		last->succ = nullptr;
		delete temp;
	} 
} 

template <typename T> 
void List<T>::pop_front() {
	if (first != last) {
		--ctr;
		Node<T> *temp = first;
		first = temp->succ;
		first->pred = nullptr;
		delete temp;
	} 
} 

template <typename T> 
List<T>::~List() {
	while (first) {
		Node<T> *temp = first;
		first = first->succ;
		if (first) 
			first->pred = nullptr;
		delete temp;
	}
}

// friend functions
template <typename T>
ostream &print(ostream &os, List<T> &l) {
	for (typename List<T>::iterator it = l.begin(); 
	                                 it != l.end(); ++it)
			os << *it << " ";
	return os;
}

#endif