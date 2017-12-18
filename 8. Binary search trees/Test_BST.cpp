#include "BST.h"
#include <deque>
#include <iostream>
#include <string>

using std::cout;
using std::deque;
using std::endl;
using std::string;

int main() {
	BST<int, string> tree;
	
	tree.insert(9, "Z");
	tree.insert(1, "C");
	tree.insert(6, "E");
	tree.insert(7, "R");
	tree.insert(2, "D");
	tree.insert(3, "B");
	tree.insert(12, "H");
	tree.insert(5, "A");
	tree.insert(8, "B");
	tree.insert(4, "I");
	tree.insert(10, "G");
		
	cout << "Print tree in increasing order by key (format: (key, value)): " << endl;
	print(cout, tree) << endl << endl;
	
	
	cout << "Min key in BST: ";
	cout << tree.min()->get_key() << " " << tree.min()->get_value() << endl<< endl;
	cout << "Max key in BST: ";
	cout << tree.max()->get_key() << " " << tree.max()->get_value() << endl << endl;
	cout << "Size of BST : " << tree.size() << endl << endl;
	cout << "Depth of BST : " << tree.depth() << endl << endl;
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
	
	deque<Node<int, string>> q;
	int k1(70), k2(100);
	q = tree.range_search(k1, k2);
	
	cout << "Range of nodes between " << k1 << " and " << k2 << ": " << endl;
	if (q.empty())
		cout << "empty" << endl << endl;
	else {
		for (auto it = q.begin(); it != q.end(); ++it) {
			cout << it->get_key() << " ";
		}
		cout << endl;	
	}
}