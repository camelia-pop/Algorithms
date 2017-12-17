#include "Board.h"
#include <utility>

using std::cout;
using std::endl;
using std::swap;
using std::to_string;

Board::Board(size_t m): n(m), board(vector<size_t>(m*m, 0)) { 
	for (size_t i = 0; i != board.size() - 1; ++i) 
		board[i] = i + 1;		
} 

size_t Board::hamming() const {
	size_t k = 0;
	for (size_t i = 0; i != board.size(); ++i) 
		k += ((board[i] != i + 1) && (board[i]));
	return k;
}

size_t Board::manhattan() const {
	size_t k = 0;
	for (size_t i = 0; i != board.size(); ++i) 
		if (board[i]) 
			k += (abs((board[i]-1)/n - i/n) + abs((board[i]-1)%n-i%n));	
	return k;
}

bool Board::operator==(const Board &bd) const {
	return this->toString() == bd.toString();
}

bool Board::operator!=(const Board &bd) const {
	return this->toString() != bd.toString();	
}

Board Board::twin() const {
	Board boardTwin(board);
	size_t i = 0;
	while ((i != n*n) && (!board[i] || (boardTwin.board[i] == i + 1))) 		++i;
	if (i == n*n) // every element is in place
		swap(boardTwin.board[0], boardTwin.board[1]);
	else
		if (i == n*n - 1)
			swap(boardTwin.board[n*n - 1], boardTwin.board[n*n - 3]);
		else
			(boardTwin.board[i + 1]) 
				? swap(boardTwin.board[i], boardTwin.board[i + 1]) 
				: swap(boardTwin.board[i], boardTwin.board[i + 2]); 
	return boardTwin;
}

vector<Board> Board::neighbors() const {
	// find the position of 0;
	size_t i = 0;
	while (board[i]) ++i;
	
	vector<Board> vOfNeighbors;
	Board temp = *this;
	// North	
	if (i >= n) {
		swap(temp.board[i], temp.board[i-n]);
		vOfNeighbors.push_back(temp);
		swap(temp.board[i], temp.board[i-n]);
	}
	// South
	if (i < n*n - n) {
		swap(temp.board[i], temp.board[i+n]);
		vOfNeighbors.push_back(temp);
		swap(temp.board[i], temp.board[i+n]);
	}
	// East	
	if (i % n < n-1) {
		swap(temp.board[i], temp.board[i+1]);
		vOfNeighbors.push_back(temp);
		swap(temp.board[i], temp.board[i+1]);
	}
	// West	
	if (i % n > 0 ) {
		swap(temp.board[i], temp.board[i-1]);
		vOfNeighbors.push_back(temp);
		swap(temp.board[i], temp.board[i-1]);
	}	
	return vOfNeighbors;
}

string Board::toString() const {
	string s;
	s += to_string(n) + "\n";
	for (size_t i = 0; i != n; ++i) {
		for (size_t j = 0; j != n; ++j) 
			s += to_string(board[i * n + j]) + " ";
		s += "\n";
	}
	s += "\n";
	return s;
}

ostream &operator<<(ostream &os, const Board &bd) {
	os << endl << bd.toString() << endl;
	return os;
}


