#ifndef SUCCESSOR_H
#define SUCCESSOR_H

#include <iostream>

using std::endl;
using std::ostream;
using std::size_t;

class Successor {
	friend ostream &print(ostream &, const Successor &);
	public:
		Successor(size_t m = 1);
		void link(size_t, size_t);
		void remove(size_t);
		size_t successor(size_t) const;
		bool empty() const { return succ[root(0)] == n; }
		~Successor() {
			delete [] id; delete [] sz; delete [] succ; 
		};
	private:
	    size_t root(size_t) const;		
		size_t n;
		size_t *id, *sz, *succ;
};

#endif