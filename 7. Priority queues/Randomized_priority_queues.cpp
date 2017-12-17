/*
Statement of the problem:
Randomized priority queue. Describe how to add the methods sample() and delRandom() to our binary heap implementation. 
The two methods return a key that is chosen uniformly at random among the remaining keys, with the latter method also removing that key. 
The sample() method should take constant time; the delRandom() method should take logarithmic time. Do not worry about resizing the underlying array.

Solution:
Add methods sample() and delRandom() to class PQ
*/

#include "PQ.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	PQ<int> pq;
	pq.insert(1);
	pq.insert(8);
	pq.insert(15);
	pq.insert(3);
	pq.insert(10);
	pq.insert(5);
	
	cout << "Elements of PQ: ";
	print(cout, pq) << endl << endl;
	cout << "A sample element: " << pq.sample() << endl << endl;
		
	pq.delRandom();
	cout << "Elements of PQ after deleting a random element: ";
	print(cout, pq) << endl << endl;	
}