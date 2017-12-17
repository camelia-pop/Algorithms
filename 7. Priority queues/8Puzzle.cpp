#include "Board.h"
#include "PQ.h"
#include "Solver.h"
#include <ostream>
#include <functional>

using std::cout;
using std::endl;
using std::less;
using std::ostream;

int main() {
	//vector<size_t> b = {0, 1, 3, 4, 2, 5, 7, 8, 6};
	vector<size_t> b = {8, 1, 3, 4, 0, 2, 7, 6, 5};
	//vector<size_t> b = {2, 4, 0, 1, 3, 5, 7, 6, 8};
	//vector<size_t> b = {1, 2, 4, 3, 5, 6, 7, 0, 8};
	//vector<size_t> b = {4, 2, 0, 1, 3, 5, 7, 6, 8};
	Board bd(b);

	cout << "Initial board: " << endl;
	cout << bd << endl;
		
	Solver sol(bd);
	vector<Board> seqMoves(sol.solution());
	if (sol.isSolvable()) {
		cout << "Moves: " << endl;
		for (Board b : seqMoves)
			cout << b;
		cout << "Number of moves taken: " << seqMoves.size() << endl;
	} else 
		cout << "Board is not solvable" << endl;	
}