#include "SeamCarver.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <math.h>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::numeric_limits;
using std::stack;
using std::vector;

SeamCarver::SeamCarver(ifstream &is) {
	// read the data from the input file
	is >> H >> V;
	size_t colorR, colorG, colorB;
	vector<size_t> r, g, b;
	while (is >> colorR >> colorG >> colorB) {
		r.push_back(colorR);
		g.push_back(colorG);
		b.push_back(colorB);
	}
	// create the private members
	en = vector<double>(H*V, numeric_limits<double>::max());
	double maxEn = 0, deltaX, deltaY;
	// en[] in the interior
	for (size_t i = H+1; i != H*V; ++i) {
		if ((i % H == 0) || ((i + 1) % H == 0) || (i >= H*(V-1)))
			continue;
		deltaX = (r[i-1] - r[i+1]) * (r[i-1] - r[i+1])
		         + (g[i-1] - g[i+1]) * (g[i-1] - g[i+1])
				 + (b[i-1] - b[i+1]) * (b[i-1] - b[i+1]);
		deltaY = (r[i-H] - r[i+H]) * (r[i-H] - r[i+H])
		         + (g[i-H] - g[i+H]) * (g[i-H] - g[i+H])
				 + (b[i-H] - b[i+H]) * (b[i-H] - b[i+H]);		 
		en[i] = sqrt(deltaX + deltaY);
		if (maxEn < en[i])
			maxEn = en[i];	
	}
	// en[] on the margins
	for (size_t i = 0; i != H; ++i) 
		en[i] = en[i + H*(V-1)] = maxEn;
	for (size_t i = 0; i != V; ++i) 
		en[H*i] = en[H*i + H - 1] = maxEn;
}

double SeamCarver::energy(int x, int y) const {
	if ((x < 0) || (x >= H) || (y < 0) || (y >= V))
		return -1;
	return en[y * H + x];	
}

vector<int> SeamCarver::findVerticalSeam() const {
	vector<int> prev(H*V, -1);
	vector<double> distTo(H*V, numeric_limits<double>::max());
	size_t j;
	for (size_t i = 0; i != H; ++i)
		distTo[i] = en[i];
	for (size_t i = H; i != H*V; ++i) {
		// upward neighbors of i: i - H - 1, i - H, i - H + 1;
		for (int j = -1; j != 2; ++j)
			relaxVertical(i, i - H + j, distTo, prev);
	}
	// check for the shortest energy seam;
	double minEn = numeric_limits<double>::max();
	size_t iend;
	for (size_t i = H*(V-1); i != H*V; ++i)
		if (minEn > distTo[i]) {
			minEn = distTo[i];
			iend = i;
		}
	
	stack<int> st;
	for (int i = iend; i != -1; i = prev[i]) 
		st.push(i);
	vector<int> vertSeam;
	while (!st.empty()) {
		vertSeam.push_back(st.top());
		st.pop();
	}
	return vertSeam;
}

void SeamCarver::removeVerticalSeam() {
	vector<int> vertSeam = findVerticalSeam();
	size_t i = 0, k = 0;
	while (i != H*V) {
		if (i == vertSeam[k]) 
			++k;
		else
			en[i-k] = en[i];
		++i;
	}
	--H;
	vertSeam.resize(H*V);	
}

// helper function
void SeamCarver::relaxVertical(size_t i, size_t j, 
	 vector<double> &distTo, vector<int> &prev) const {
	// check for out of bounds indices
	if ((i < 0)	|| (i >= H*V))
		return;
	if ((j < 0)	|| (j >= H*V))
		return;
	// check for left margin
	if ((i % H == 0) && (j == i - H - 1) )
		return;
	// check for right margin
	if (((i + 1) % H == 0) && (j == i - H + 1) )
		return;
	// do the relaxation
	if (distTo[i] > distTo[j] + en[i]) {
		distTo[i] = distTo[j] + en[i];
		prev[i] = j;
	}
}
