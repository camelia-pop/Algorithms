/******************************************
* Implementation of class PercolationStats
*******************************************/

#include "PercolationStats.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <vector>

using std::accumulate;
using std::cout;
using std::endl;
using std::make_pair;
using std::vector;

pair<double, double> PercolationStats::simulation() {
	size_t i, j;
	// for each simulation i = 0, ..., T-1, propOpenSites[i] record the proportion of open sites when the network begins to percolate
	vector<double> propOpenSites(T);
	
	// initialization of seed in the random number generator for performing the simulations
	time_t seconds;
	time(&seconds);
	srand((unsigned int) seconds);
	
	for (int t = 0; t != T; ++t) {
		Percolation perc(n);
		while (!perc.percolates()) {
			i = rand() % n;
			j = rand() % n;
			if (!perc.isFull(i, j))
				perc.open(i, j);
		}
		propOpenSites[t] = (1.0 * perc.numberOfOpenSites()) / (n*n);
	}
	// find the sample mean of the simulated values
	double av = accumulate
			(propOpenSites.begin(), propOpenSites.end(), 0.0) / T;
	// find the sample variance of the simulated values
	double sigma = 0.0;		
	for (int t = 0; t != T; ++t)
		sigma += 
			(propOpenSites[t] - av)*(propOpenSites[t] - av);
	sigma /= (T-1);
	// take the square root of the sample variance
	sigma = sqrt(sigma);
	return make_pair(av, sigma);
}

