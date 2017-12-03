/*******************************************************************
* Implementation of class Weighted Quick Union-Find 
* with Path Compression with find largest element (WQUFPC_largest) 
*******************************************************************/

#ifndef WQUFPC_largest_H
#define WQUFPC_largest__H

#include <iostream>

using std::ostream;
using std::size_t;

class WQUFPC_largest {
	friend ostream &print(ostream&, const WQUFPC_largest&);
	public:		
		WQUFPC_largest(size_t m = 1);
		void link(size_t, size_t);
		bool connected(size_t, size_t) const;
		bool connected() const { return sz[root(0)] == n; };
		size_t find(size_t i) const { return largest[root(i)]; };
		~WQUFPC_largest() { 
			delete [] id; delete [] largest; delete [] sz; 
		};
	private:
		size_t root(size_t) const;
		void check(size_t) const;	
		
		size_t n;		
		size_t *id, *largest, *sz;		
};

#endif