#include "SeamCarver.h"
#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::vector;

int main() {
	ifstream is("5by5.txt");
	SeamCarver sc(is);
	is.close();
	cout << "Energy matrix: " << endl;
	cout << sc.width() << endl;
	cout << sc.height() << endl;
	cout << endl;
	for (size_t y = 0; y != sc.height(); ++y) {	
		for (size_t x = 0; x != sc.width(); ++x) 
			cout << sc.energy(x, y) << " ";
		cout << endl;
	}
	cout << endl << endl;
	
	sc.removeVerticalSeam();
	
	cout << "Energy matrix after removing a vertical seam: " << endl;
	cout << sc.width() << endl;
	cout << sc.height() << endl;
	cout << endl;
	for (size_t y = 0; y != sc.height(); ++y) {	
		for (size_t x = 0; x != sc.width(); ++x) 
			cout << sc.energy(x, y) << " ";
		cout << endl;
	}
	cout << endl << endl;
	
}