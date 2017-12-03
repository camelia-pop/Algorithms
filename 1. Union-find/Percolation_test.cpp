/*
This programming assignment estimates the value of the critical probability p_c when a system begins to percolate.
The system is here a n-by-n matrix of closed sites.
We choose with equal probability to open a site. We stop the first time when there is a path of open sites connecting the first row 
of the matrix to the last row. The proportion of open sites is a sample of the critical probability when the system begins to percolate.
A brief introduction to percolation theory and the definition of critical probability can be found at the Wikipedia link:
https://en.wikipedia.org/wiki/Percolation_theory
*/

#include "Percolation.h"
#include "PercolationStats.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	PercolationStats ps(5, 100);
	cout << ps.mean() << " " << ps.stddev() << endl;
	
}
