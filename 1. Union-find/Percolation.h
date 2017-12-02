/*********************************
* Interface of class Percolation
*********************************/

#ifndef PERCOLATION_H
#define PERCOLATION_H

#include "WQUFPC.h"

class Percolation {
	friend ostream &print(ostream&, const Percolation&);
	public:
		Percolation(size_t m = 1);
		bool isOpen(size_t i, size_t j) const {
			return check(i) && check(j) && a[i][j]; 
		};
		void open(size_t, size_t);
		int numberOfOpenSites() const;
		bool percolates() const { return rep.connected(0, n*n+1); };
		bool isFull(size_t i, size_t j) const { return a[i][j]; };	
		~Percolation();
	private:
		bool check(size_t i) const { return (i < n); };
		size_t n;
		// rep is a WQUFPC (Weighted Quick Union-Find with Path Compression) object in which we connect the open sites of the matrix a
		WQUFPC rep; 
		// a is n by n matrix which indicated the open/closed sites
		bool **a;
};

#endif
