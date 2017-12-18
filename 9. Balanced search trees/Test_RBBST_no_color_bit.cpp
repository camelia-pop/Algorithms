/*
Statement of the problem:
Red–black BST with no extra memory. Describe how to save the memory for storing the color information when implementing a red–black BST.

Solution:
Create class RBBST_no_color_bit.h. 
A node is red if the key in the left child is smaller than its key and the key in the right child is larger than its key.
A node is black if the key in the left child is *larger* than its key and the key in the right child is *smaller* than its key.
We define two static Node pointers -- null1 and null2. When we create a node, the node is red if the left child is null2 and the right child null1, and the node is black if the left child is null1 and the rights child is null2.  
*/

#include "RBBST_no_color_bit.h"
#include <string>

using std::string;

int main() {
	RBBST_no_color<int, string> tree;
	
	tree.insert(5, "A");
	tree.insert(8, "C");
	tree.insert(9, "A");
	tree.insert(3, "A");
	tree.insert(2, "B");
	tree.insert(6, "A");
	tree.insert(7, "B");
	tree.insert(12, "B");
	tree.insert(-2, "B");
	tree.insert(10, "B");
	tree.insert(0, "B");
	
	cout << "Elements of BST: " << endl;
	print(cout, tree) << endl << endl;
	
	cout << "Size of RBBST = " << tree.size() << endl << endl;
	
	cout << "Depth of RBBST = " << tree.depth() << endl << endl;
}
