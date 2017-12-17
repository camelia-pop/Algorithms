#ifndef BOARD_H
#define BOARD_H

#include <cmath>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using std::greater;
using std::ostream;
using std::size_t;
using std::string;
using std::vector;

class Board;

ostream &operator<<(ostream &, const Board &);

class Board {	
	public:
		Board(size_t);
		// will not implement this constructor because C++ requires that we specify all sizes except for the first coordinate, which is not possible for this application.
		// Board(const size_t b[][*], size_t);
		Board(vector<size_t> b): n(sqrt(b.size())), board(b) {};
		size_t hamming() const; // number of blocks out of place
		size_t manhattan() const; // sum of manhattan distances
		bool operator==(const Board &) const;
		bool operator!=(const Board &) const;
		bool operator<(const Board &bd) const { 
			return manhattan() < bd.manhattan();
		};
		bool operator>(const Board &bd) const { 
			return manhattan() > bd.manhattan();
		};
		bool isGoal() const { return *this == Board(n); };
		Board twin() const;
		vector<Board> neighbors() const;
		size_t dimension() const { return n; };
		string toString() const;
	private:	
		size_t n;
		vector<size_t> board;
};



#endif