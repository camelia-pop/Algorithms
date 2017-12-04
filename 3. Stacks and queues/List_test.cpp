#include "List.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
	List<string> li;
	li.push_back("abc");
	li.push_back("def");
	li.push_front("oit");
	cout << "List elements: ";
	print(cout, li) << endl << endl;
	
	cout << "Remove one element from the back: ";
	li.pop_back();
	print(cout, li) << endl << endl;
	cout << "Size of the list: " << li.size() << endl << endl;
	cout << "Is the list empty? " << li.isEmpty() << endl << endl;
	li.pop_front();
	li.pop_front();
	li.pop_front();
	
	cout << "List after removing 3 elements: ";
	print(cout, li) << endl << endl;
	cout << "Size of the list: " << li.size() << endl << endl;
	cout << "Is the list empty? " << li.isEmpty() << endl << endl;
	
}