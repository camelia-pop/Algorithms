/*******************************************************************
* Implementation of class Weighted Quick Union-Find 
* with Path Compression (WQUFPC)
*******************************************************************/

#include "WQUFPC.h"
#include <stdexcept>

using std::cout;
using std::endl;
using std::range_error;

WQUFPC::WQUFPC(size_t m): 
	n(m), id(new size_t[m]), sz(new unsigned[m]) {
		for (size_t i = 0; i != m; ++i) {
			id[i] = i;
			sz[i] = 1;
		}
}

void WQUFPC::link(size_t i, size_t j) {
	check(i); check(j);
	size_t ri = root(i), rj = root(j);
	if (ri != rj) {
		if (sz[ri] < sz[rj]) {
			id[ri] = rj; sz[rj] += sz[ri];
		} else {
			id[rj] = ri; sz[ri] += sz[rj];
		}	
	}
}

bool WQUFPC::connected(size_t i, size_t j) const {
	check(i); check(j);
	return root(i) == root(j);
}

// utility functions

size_t WQUFPC::root(size_t i) const {
	check(i);
	/*
	//In the while loop below we are updating the size of the nodes that are not roots, but this is not important for finding the connected components, and so it is better not to update them so that we don't do extra work.
	
	while (i != id[i]) {
		if (id[i] != id[id[i]]) {
			sz[id[i]] -= sz[i];
			id[i] = id[id[i]]; 
			i = id[i];		
		} else {
			i = id[i];		
		}
	}
	*/
	// find the root and do also path compression in one-pass
	while (i != id[i]) {
		id[i] = id[id[i]]; 
		i = id[i];				
	}
}

void WQUFPC::check(size_t i) const {
	if (i >= n)
		throw range_error("Out-of-bound error in union");
}

// friend functions
ostream &print(ostream &os, const WQUFPC &connected_comp) {
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
