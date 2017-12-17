#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"
#include "PQ.h"
#include <vector>

using std::vector;

class Node {
	friend class Solver;
	public:
		Node(const Board &b1, const Board &b2, size_t n): 
			board(b1), prevBoard(b2), numMoves(n) {};
		size_t priority() const { 
			return numMoves + board.manhattan(); 
		};
		bool operator>(const Node &nd) const {
			return priority() > nd.priority();
		};
	private:
		Board board;
		Board prevBoard;
		size_t numMoves; // number of moves needed to get to this board	
};

class Solver {
	public:
	    // Don't like how previousBoard is initialized
		Solver(Board);			
		bool isSolvable() { return seqMoves.size(); };				
		size_t moves() { return seqMoves.size(); };
		vector<Board> solution() { return seqMoves; };				
	private:
		Node currNode;
		PQ<Node, greater<Node>> pqNodes;
		vector<Board> seqMoves;
};


#endif