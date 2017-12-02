/**************************************
* Implementation of class Percolation
**************************************/

#include "Percolation.h"

using std::endl;

Percolation::Percolation(size_t m): 
	n(m), rep(m*m + 2), a(new bool*[m]) {
	for (size_t i = 0; i != m; ++i) {
		a[i] = new bool[m];
		for (size_t j = 0; j != m; ++j)
			a[i][j] = false;
	}	
}

// i, j can take values 0, 1, ..., n-1
void Percolation::open(size_t i, size_t j) {
	if (!check(i) || !check(j))  return;
	a[i][j] = true;
	size_t k(i*n+j+1);
	// Up
	if (i == 0)  rep.link(k, 0);
	else if (a[i-1][j])  rep.link(k, k-n);
	// Down	
	if (i == n-1) rep.link(k, n*n+1);
	else if (a[i+1][j])  rep.link(k, k+n);
	// Left
	if (j && a[i][j-1]) rep.link(k, k-1);
	// Right
	if ((j < n-1) && a[i][j+1]) rep.link(k, k+1);
}	

int Percolation::numberOfOpenSites() const {
	int s(0);
	for (size_t i = 0; i != n; ++i) 
		for (size_t j = 0; j != n; ++j)
			s += a[i][j];
	return s;	
}

Percolation::~Percolation() {
	for (size_t i = 0; i != n; ++i)
			delete [] a[i];
} 	

// friend functions
ostream &print(ostream &os, const Percolation &perc) {
	print(os, perc.rep) << endl << endl;
	for (size_t i = 0; i != perc.n; ++i) {
			for (size_t j = 0; j != perc.n; ++j)
				os << perc.a[i][j] << " ";
			os << endl;
	}
}	
