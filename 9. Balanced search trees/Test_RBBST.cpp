#include "RBBST.h"
#include <string>

using std::string;

int main() {
	RBBST<int, string> tree;
	
	tree.insert(5, "A");
	tree.insert(3, "A");
	tree.insert(2, "B");
	tree.insert(6, "A");
	tree.insert(7, "B");
	tree.insert(8, "C");
	tree.insert(9, "A");
	tree.insert(12, "B");
	tree.insert(-2, "B");
	tree.insert(10, "B");
	tree.insert(0, "B");
	
	cout << "Elements in BST: " << endl;
	print(cout, tree) << endl << endl;
	
	cout << "Size of BST = " << tree.size() << endl << endl;
	
	cout << "Depth of BST = " << tree.depth() << endl << endl;
}