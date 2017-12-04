/*
Queue with two stacks. 
Implement a queue with two stacks so that each queue operations takes a constant amortized number of stack operations.

Solution:
Use two stacks st1 and st2, which we use as follows. 
When we are adding an element to the queue, we are adding it in st1.
When we are popping an element from the queue, we move all the elements from st1 to st2, we pop the top element from st2, and then we move again the elements in st1.
*/

#include "QueueWithStacks.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
	QueueWithStacks<string> q;
	q.pop();
	q.push("abc");
	q.push("def");
	q.emplace(5, 'r');	
	
	cout << "Size: " << q.size() << endl;
	cout << "Is empty: " << q.empty() << endl;
	cout << "Front element: " << q.front() << endl;
	cout << "Back element: " << q.back() << endl;
	q.front() = "wer";
	cout << "New front element: " << q.front() << endl;
	q.pop();
	cout << "New front element: " << q.front() << endl;
	
	cout << endl << "Elements of the queue: ";
	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}