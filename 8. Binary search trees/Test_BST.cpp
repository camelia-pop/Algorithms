#include "BST.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
	BST<int, string> tree;
	
	tree.insert(5, "A");
	tree.insert(3, "B");
	tree.insert(1, "C");
	tree.insert(2, "D");
	tree.insert(4, "I");
	tree.insert(7, "R");
	tree.insert(6, "E");
	tree.insert(8, "B");
	
	cout << "Min key in BST: ";
	cout << tree.min()->get_key() << " " << tree.min()->get_value() << endl;
	cout << "Max key in BST: ";
	cout << tree.max()->get_key() << " " << tree.max()->get_value() << endl;
	cout << endl;
	
	cout << "Print tree in increasing order by key (format: (key, value)): " << endl;
	print(cout, tree) << endl << endl;
	
	cout << "Value at 3: " << tree.get(3) << endl << endl;
	
	cout << "Delete 4" << endl;
	tree.deleteNode(4);
	cout << "Print tree in increasing order by key (format: (key, value)): " << endl;
	print(cout, tree) << endl << endl;
	
	cout << "Rank of 4: " << tree.rank(4) << endl << endl;
	cout << "Floor of 4: " << tree.floor(4) << endl << endl;
	cout << "Ceiling of 4: " << tree.ceiling(4) << endl << endl;
	
	cout << "Morris inorder non-recusive traversal" << endl;
	tree.morrisTraversal();
	cout << endl << endl;
	
	cout << "Inorder non-recusive traversal with stack" << endl;
	tree.stackTraversal();
	cout << endl << endl;
	
	
}