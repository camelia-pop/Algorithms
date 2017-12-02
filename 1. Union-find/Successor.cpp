#include "Successor.h"
#include <stdexcept>

using std::cout;
using std::out_of_range;

Successor::Successor(size_t m): 
	n(m), id(new size_t[m+1]), sz(new size_t[m+1]), 
	succ(new size_t[m+1]) {
	for (size_t i = 0; i != m+1; ++i) {
		id[i] = succ[i] = i;
		sz[i] = 1;
	}
}

void Successor::link(size_t i, size_t j) {
	if ((i > n) || (j > n)) 
		throw out_of_range("Index is remove\n");
	i = root(i); j = root(j);	
	if (i != j) {
		succ[i] = succ[j] = (i > j)? succ[i] : succ[j];
		if (sz[i] < sz[j]) {
			id[i] = j; sz[j] += sz[i]; 			
		} else {
			id[j] = i; sz[i] += sz[j];			
		}	
	}
}
	
void Successor::remove(size_t i) {
	if (i >= n) 
		throw out_of_range("Index is remove\n");
	link(i, i+1);	
}

size_t Successor::successor(size_t i) const {
	if (i > n) 
		throw out_of_range("Index is successor\n");
	return succ[root(i)];
}		
		
ostream &print(ostream &os, const Successor &rec) {
	os << "Successors: ";
	for (size_t i = 0; i != rec.n; ++i) 
		os << rec.successor(i) << " ";
	os << endl;	
}

// utility function

size_t Successor::root(size_t i) const {
	if (i > n) 
		throw out_of_range("Index is root\n");
	while (i != id[i]) {
		id[i] = id[id[i]]; 
		i = id[i];				
	}
	return i;
}