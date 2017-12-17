#include "PQ.h"
#include <ctime>
#include <functional>

using std::greater;

int main () {
	PQ<int, greater<int>> pq;
	
	pq.insert(1);
	pq.insert(2);
	pq.insert(0);
	pq.insert(6);
	
	cout << "Elements of PQ: ";
	print(cout, pq) << endl;
	cout << " top element = " << pq.top() << " size = " << pq.size() << endl << endl;
	
	srand(time(0));
	pq.delRandom();
	cout << "PQ after deleting a random element: ";
	print(cout, pq) << endl;
	cout << " top element = " << pq.top() << " size = " << pq.size() << endl << endl;
	cout << "A random sample element = " << pq.sample() << endl << endl;
	
	pq.removeTop(); 
	cout << "Elements of PQ after removing the top: ";
	print(cout, pq) << endl;
	cout << " top element = " << pq.top() << " size = " << pq.size() << endl << endl;
	
	
	pq.removeTop(); 
	cout << "Elements of PQ after removing the top: ";
	print(cout, pq) << endl;
	cout << " top element = " << pq.top() << " size = " << pq.size() << endl << endl;
	
	/*
	// test removing from an empty priority queue
	pq.removeTop(); 
	cout << "Elements of PQ after removing the top: ";
	print(cout, pq) << endl;
	cout << " top element = " << pq.top() << " size = " << pq.size() << endl << endl;
	*/
	
	vector<int> x {4, 3, 6, 2, 7};
	
	cout << "Vector x: ";
	for (auto it = x.begin(); it != x.end(); ++it)
		cout << *it << " ";
	cout << endl;
	
	heapSort(x.begin(), x.end());
	cout << "Vector x sorted in decreasing order: ";
	for (auto it = x.begin(); it != x.end(); ++it)
		cout << *it << " ";
	cout << endl;
	
	heapSort(x.rbegin(), x.rend());
	cout << "Vector x sorted in increasing order: ";
	for (auto it = x.begin(); it != x.end(); ++it)
		cout << *it << " ";
	cout << endl;
}