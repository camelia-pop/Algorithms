/*******************************************************************
* Interface of class Weighted Quick Union-Find with Path Compression 
* (WQUFPC)
*******************************************************************/

#ifndef WQUFPC_H
#define WQUFPC_H

#include <iostream>

using std::ostream;
using std::size_t;

class WQUFPC {
	friend ostream &print(ostream&, const WQUFPC&);
	public:		
		WQUFPC(size_t m = 1);
		void link(size_t, size_t);
		bool connected(size_t, size_t) const;
		bool connected() const { return sz[root(0)] == n; };
		~WQUFPC() { delete [] id; delete [] sz; };
	private:
		size_t root(size_t) const;
		void check(size_t) const;	
		
		size_t n;
		size_t *id;
		unsigned *sz;
};

#endif
