/*******doubl*******************************
* Interface of class PercolationStats
**************************************/

#ifndef PERCOLATION_STATS_H
#define PERCOLATION_STATS_H

#include "Percolation.h"
#include <cmath>
#include <utility>

using std::pair;

class PercolationStats {
	public:
		PercolationStats(size_t m = 1, size_t numIt = 100):
			n(m), T(numIt) { stats = simulation(); };
		double mean() const	{ return stats.first; };
		double stddev() const { return stats.second; };		
		double confidenceLo() const { 
			return stats.first - 1.96 * stats.second / sqrt(T); 
		};
		double confidenceHi() const { 
			return stats.first + 1.96 * stats.second / sqrt(T); 
		};		
	private:
		// simulation() finds a sample of size T for the value of the percolation probability, and returns a pair in which the first component is the sample mean and the second component is the square root of the sample variance
		pair<double, double> simulation();
		
		size_t n;
		unsigned T;
		pair<double, double> stats;			
};

#endif