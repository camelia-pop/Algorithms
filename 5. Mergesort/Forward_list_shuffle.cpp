/*
Statement of the problem:
Shuffling a linked list. Given a singly-linked list containing n items, rearrange the items uniformly at random. Your algorithm should consume a logarithmic (or constant) amount of extra memory and run in time proportional to n*log(n) in the worst case.

Solution:
We create a Forward_list class and we add a data member shuffle().
*/

#include "Forward_list.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	Forward_list l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.push_back(6);
	
	cout << "List before shufflind: ";
	print(cout, l) << endl << endl;
	
	cout << "List after shuffling: ";
	l.shuffle();
	print(cout, l) << endl << endl;
}