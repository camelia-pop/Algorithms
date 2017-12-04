/*
Stack with max. 
Create a data structure that efficiently supports the stack operations (push and pop) and also a return-the-maximum operation. 
Assume the elements are reals numbers so that you can compare them.

Solution:
Implement the stack class using a deque. Add a new deque data member in which we add an element each time it becomes the current max. 
*/

#include "StackWithMax.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	StackWithMax<int> st;
	st.push(2);
	st.push(1);
	st.push(3);
	st.push(2);
	cout << st.front() << " " << st.max() << endl;
	st.pop();
	cout << st.front() << " " <<  st.max() << endl;
	st.pop();
	cout << st.front() << " " <<  st.max() << endl;
	st.pop();
	cout << st.front() << " " <<  st.max() << endl;
	st.pop();
	cout << st.front() << " " <<  st.max() << endl;
	st.pop();
		
}