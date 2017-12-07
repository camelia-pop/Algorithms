/************************************
* Singly - linked list of integers
*************************************/
#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <iostream>
#include <utility>

using std::ostream;
using std::pair;

class Node {	
	public:
		Node(int n = 0) : val(n), next(nullptr) {};
		~Node() { next = nullptr; };
		
		int val;
		Node *next;
};

class Forward_list;

ostream &print(ostream &, const Forward_list &);

class Forward_list {
	friend ostream &print(ostream&, const Forward_list&);
	public:
		Forward_list(): head(nullptr), last(nullptr) {};
		void push_back(int);
		size_t size() const;
		void shuffle();	
		~Forward_list();	
	private:
		// helper functions for shuffle()
		pair<Node*, Node*> middle(Node*, Node*, size_t) const;
		void merge(Node*, size_t, Node*, Node*, size_t);
		void divide_and_merge(Node*, Node*, size_t);		
		
		Node *head, *last;		
};

#endif