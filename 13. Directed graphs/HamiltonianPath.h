#ifndef HAMILTONIAN_PATH_H
#define HAMILTONIAN_PATH_H

#include "Digraph.h"
#include "TopologicalSort.h"

class HamiltonianPath {
	public:
		HamiltonianPath(const Digraph &G);
		bool hasHamiltonianPath() const { return HamPathExists; };	
		stack<size_t> HamPath() const { 
			return HamPathExists ? revPostOrder : stack<size_t>(); 
		};
	private:
		stack<size_t> revPostOrder;
		bool HamPathExists;
};

#endif