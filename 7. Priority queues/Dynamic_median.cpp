/*
Statement of the problem:
Dynamic median. Design a data type that supports insert in logarithmic time, find-the-median in constant time, and remove-the-median in logarithmic time.

Solution:
Create a tree structure that has two priority queues: a max priority queue (low -- it holds the first half of the elements) and a min priority queue (high -- it holds the second half of the elements).  

When the number of elements is odd, the low priority queue will have one extra element that the high priority queue. Otherwise, the two priority queues have the same size.
*/

#include "Median.h"
#include <functional>
#include <iostream>

using std::cout;
using std::endl;
using std::less;

int main() {
	Median<int> med;
	med.insert(5);
	med.insert(6);
	med.insert(7);
	med.insert(1);
	
	cout << "Structure of median: " << endl;
	print(cout, med) << endl;
	cout << "Median: " << med.median() << endl << endl;
	
	med.removeMed();
	print(cout, med) << endl << endl;
	cout << "Median: " << med.median() << endl << endl;
	
	med.removeMed();
	print(cout, med) << endl << endl;
	cout << "Median: " << med.median() << endl << endl;
	
	med.removeMed();
	print(cout, med) << endl << endl;
	cout << "Median: " << med.median() << endl << endl;
	
	/*
	// test for no elements
	med.removeMed();
	print(cout, med) << endl << endl;
	cout << "Median: " << med.median() << endl << endl;
	*/
	
	ComplementComparator<int, less<int>> cc;
	cout << "Test of complement comparator: 3 >= 3 ? ";
	if (cc(3, 3))
		cout << "true" << endl;
	else
		cout << "false" << endl;
}