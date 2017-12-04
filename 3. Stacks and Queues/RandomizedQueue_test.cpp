/*
The implementation of the class RandomizedQueue uses ideas from the implementation of the vector class as presented in Chapter 16 in C++ Primer, by Stanley B. Lippman,‎ Josée Lajoie and‎ Barbara E. Moo.
*/
#include "RandomizedQueue.h"
#include <fstream>
#include <string>

using std::ifstream;
using std::string;

int main() {
	RandomizedQueue<string> rq;
	
	cout << "Add element 1abc to the queue: \n\t";
	rq.enqueue("1abc");
	print(cout, rq) << endl << endl; 
	
	cout << "Add element 1efg to the queue: \n\t";
	rq.enqueue("1efg");
	print(cout, rq) << endl << endl; 
	
	cout << "Add element 1hij to the queue: \n\t";
	rq.enqueue("1hij");
	print(cout, rq) << endl << endl; 
	
	rq.enqueue("1klm");
	rq.enqueue("2abc");
	rq.enqueue("2efg");
	rq.enqueue("2hij");
	rq.enqueue("2klm");
	
	cout << "Queue after adding multiple elements: \n\t";
	print(cout, rq) << endl << endl; 
	
	rq.dequeue();
	cout <<"Queue after dequeing one element: \n\t";
	print(cout, rq) << endl << endl; 
	
	rq.dequeue();
	cout <<"Queue after dequeing two elements: \n\t";
	print(cout, rq) << endl << endl; 
	
	
	RandomizedQueue_iterator<string> it1 = rq.iterator();
	cout << "A random iterator in the queue: " << *it1 << " of size " << (*it1).size() << endl << endl;
	
	RandomizedQueue_iterator<string> it2 = rq.iterator();
	cout << "Another random iterator in the queue: " << *it2 << " of size " << it1.operator->().size() << endl << endl;
	
	cout << "Does the second random iterator have a successor in the queue? " << it2.hasNext() << endl << endl;
	it2.next(); 
	it2.next();
	it2.next();
	it2.next();
	it2.next();
	it2.next();
	it2.next();
	it2.next();
	cout << "After calling next() multiple times, does the second random iterator have a successor in the queue? " << it2.hasNext() <<endl << endl;
}