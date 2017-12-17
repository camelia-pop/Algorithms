#include "PQ.h"
#include "Solver.h"
#include <cstdio>
#include <utility>

using std::swap;

Solver::Solver(Board initialBoard): 
	currNode(initialBoard, initialBoard, 0) {
	// initialization of a twin board (it does not matter which twin board, so the function that does this should be chosen as simple as possible)
	Board boardTwin(currNode.board.twin());
	Node currNodeTwin(boardTwin, boardTwin, 0);
	PQ<Node, greater<Node>> pqNodesTwin;
	
	// initialization of the vector where we keep the sequence of nodes that we investigate
	vector<Node> seqNodes;	
	seqNodes.push_back(currNode);
	
	while (!currNode.board.isGoal() && !currNodeTwin.board.isGoal()) {
		// searching for neighbors
		for (Board b : currNode.board.neighbors()) 
			if (b != currNode.prevBoard) 
				pqNodes.insert(Node(b, currNode.board, currNode.numMoves + 1));
		// searching for neighbors for the twin board		
		for (Board b : currNodeTwin.board.neighbors()) 
			if (b != currNodeTwin.prevBoard) 
				pqNodesTwin.insert
				(Node(b, currNodeTwin.board, currNodeTwin.numMoves + 1));		
		// updating current search node and the priority queue		
		currNode = pqNodes.top();
		pqNodes.removeTop();
		seqNodes.push_back(currNode);
		// updating the current search node and the priority queue for the twin board		
		currNodeTwin = pqNodesTwin.top();
		pqNodesTwin.removeTop();		
	}
	
	if (currNodeTwin.board.isGoal()) return;
	
	// create the sequence of moves in reverse order (the priority queues of nodes contains nodes that we visited but didn't lead to a solution; here we keep only those boards in the nodes that lead to a solution)
	size_t i(seqNodes.size() - 1);		
	while (i >= 0) {
		seqMoves.push_back(seqNodes[i].board);		
		while (i && (seqNodes[i].prevBoard == seqNodes[i-1].board)) {
			--i;
			seqMoves.push_back(seqNodes[i].board);			
		}
		if (i) {
			Board retBoard(seqNodes[i].prevBoard);
			--i;
			while (i && (seqNodes[i].board != retBoard)) 
				--i;			
		} else	
			break;
	}
	
	// reverse the sequence of moves
	i = seqMoves.size() - 1;
	for (auto j = 0; j <= i/2; ++j) 		
		swap(seqMoves[j], seqMoves[i - j]);
}
	
	


