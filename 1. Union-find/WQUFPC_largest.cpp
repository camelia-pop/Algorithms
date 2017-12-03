/*******************************************************************
* Implementation of class Weighted Quick Union-Find 
* with Path Compression with find largest element (WQUFPC_largest) 
*******************************************************************/

#include "WQUFPC_largest.h"
#include <stdexcept>

using std::cout;
using std::endl;
using std::range_error;

WQUFPC_largest::WQUFPC_largest(size_t m): 
	n(m), id(new size_t[m]), largest(new size_t[m]), sz(new size_t[m]){
		for (size_t i = 0; i != m; ++i) {
			id[i] = largest[i] = i;
			sz[i] = 1;
		}
}

void WQUFPC_largest::link(size_t i, size_t j) {
	check(i); check(j);
	size_t ri = root(i), rj = root(j);
	// update the largest[] vector
	size_t l1 = largest[ri], l2 = largest[rj];
	largest[ri] = largest[rj] = (l1 > l2)? l1 : l2;

	if (ri != rj) {
		if (sz[ri] < sz[rj]) {
			id[ri] = rj; sz[rj] += sz[ri];			
		} else {
			id[rj] = ri; sz[ri] += sz[rj];			
		}	
	}
}

bool WQUFPC_largest::connected(size_t i, size_t j) const {
	check(i); check(j);
	return root(i) == root(j);
}

// utility functions
size_t WQUFPC_largest::root(size_t i) const {
	check(i);
	while (i != id[i]) {
		id[i] = id[id[i]]; 
		i = id[i];				
	}
	return i;
}

void WQUFPC_largest::check(size_t i) const {
	if (i >= n)
		throw range_error("Out-of-bound error in union");
}

// friend functions
ostream &print(ostream &os, const WQUFPC_largest &connected_comp) {
	os << "Id vector: " << endl << "\t";
	for (size_t i = 0; i != connected_comp.n; ++i) 
		os << connected_comp.id[i] << " ";
	os << endl;	
	os << "Size vector: " << endl << "\t";
	for (size_t i = 0; i != connected_comp.n; ++i) 
		os << connected_comp.sz[i] << " ";
	os << endl;	
	return os;
}