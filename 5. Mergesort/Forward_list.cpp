#include "Forward_list.h"
#include <cstdlib> 
#include <iostream>
#include <utility>

using std::cout;
using std::endl;
using std::pair;
using std::srand;
using std::swap;

Forward_list::~Forward_list() {
	while (head) {
		Node *temp = head;
		head = head->next;
		delete temp;
	}
}

void Forward_list::push_back(int n) {
	if (head) {
		last->next = new Node(n);
		last = last->next; 
	} else 
		head = last = new Node(n);
}

size_t Forward_list::size() const {
	size_t ctr = 0;
	Node *iter = head;
	while (iter) {
		++ctr;
		iter = iter->next;
	}
	return ctr;
}

/*
For shuffling a singly linked list, we use the Gilbert-Shannon-Reeds model described here:

https://en.wikipedia.org/wiki/Gilbert%E2%80%93Shannon%E2%80%93Reeds_model

See the first of the equivalent descriptions of the model. 

We divide the list into two sublists and we assume that each are independetly perfectly shuffled. One list has length l and the other has length k. Then a ordering of the elements appear with probability 1/l! and 1/k! in each list. We merge the two lists by choosing an element from the each list with probability proportional to the number of elements remaining in the corresponding list. This procedure is implemented in the merge function.
*/
void Forward_list::shuffle() {
	srand((unsigned) time(0));
	// nullptr stands for a pointer before head
	divide_and_merge(nullptr, head, size());
}

// item is an element of the list
// consider the sublist that starts at item and contains n elements
void Forward_list::divide_and_merge
	(Node *beforeItem, Node *item, size_t n) {
	if (n == 1) return;
	
	pair<Node*, Node*> pr = middle(beforeItem, item, n);
	Node *mid = pr.second;
	Node *beforeMid = pr.first;
	
	divide_and_merge(beforeItem, item, n/2);	
	divide_and_merge(beforeMid, mid, n - n/2);
	merge(item, n/2, beforeMid, mid, n - n/2);
	
}

// find the middle element between item and the (n-1)th element after item
pair<Node*, Node*> Forward_list::middle
	(Node *beforeItem, Node *item, size_t n) const {
	if (n == 1)
		return {beforeItem, item};
	size_t k;
	if (beforeItem == nullptr) {
		beforeItem = item;
		item = item->next;
		k = 1; 
		
	} else
		k = 0;
	while (k < n/2) { 
			++k;
			beforeItem = beforeItem->next;
			item = item->next; 
		}
	return {beforeItem, item};
}

/* 
Assume that the sublist that starts from left and contains l elements is shuffled. 
Also assume that the sublist that starts from right and contains k elements is shuffled.
The following procedure merges the two suffled lists into one suffled list of length l + k using the rule: the next element to be added to the merged list is chosen with probability p from the first list and with probability 1-p from the second list, where p is the number of elements that were not already chosen from the first list divided by the total number of elements that were not chosen from the two lists.
*/
void Forward_list::merge(Node *left, size_t l, 
	Node *beforeRight, Node *right, size_t k) {
	
	// il - index in the sublist starting at left
	// ir - index in the sublist starting at mid
	size_t il = 0, ir = 0;
	// for sampling probabilities
	// p uniformly distributed in [0, 1] (approximately);
	double p = (double)rand()/(double)RAND_MAX; 
	double p0 = (double) l /(double) (l + k); 
	Node *nodeLeft;
	if (p > p0) { // add element from the second list to the merged list
		swap(left->val, right->val);
		if (beforeRight == left) {
			nodeLeft = right;
			beforeRight = right;
			right = right->next;
		} else {
			beforeRight->next = right->next;
			right->next = left->next;
			left->next = right;
			nodeLeft = right;
			right = beforeRight->next;
		}
		++ir;
	} else {
		nodeLeft = left->next;
		++il;
	}	
	while ((il < l) && (ir < k)) {
		// p uniformly distributed in [0, 1] (approximately);
		p = (double)rand()/(double)RAND_MAX; 
		p0 = (double)(l - il)/(double) (l + k - il - ir); 
		if (p > p0) { // add element from the second list to the merged list
			swap(nodeLeft->val, right->val);
			if (beforeRight == nodeLeft) {
				nodeLeft = right;
				beforeRight = right;
				right = right->next;
			} else {
				beforeRight->next = right->next;
				right->next = nodeLeft->next;
				nodeLeft->next = right;
				nodeLeft = right;
				right = beforeRight->next;
			}
			++ir;
		} else { // add element from the first list to the merged list
			nodeLeft = nodeLeft->next;
			++il;			
		}	
	}
}

// friend functions
ostream &print(ostream &os, const Forward_list &l) {
	Node *iter = l.head;
	while (iter) {
		os << iter->val << " ";
		iter = iter->next;
	}
	return os;
}