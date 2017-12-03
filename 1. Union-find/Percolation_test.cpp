#include "Percolation.h"
#include "PercolationStats.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	PercolationStats ps(5, 100);
	cout << ps.mean() << " " << ps.stddev() << endl;
	
}