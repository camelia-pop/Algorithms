#ifndef SEAM_CARVER_H
#define SEAM_CARVER_H

#include <fstream>
#include <vector>

using std::ifstream;
using std::vector;

class SeamCarver {
	public:
		SeamCarver(ifstream &);
		int width() const { return H; };
		int height() const { return V; };
		double energy(int, int) const;
		vector<int> findVerticalSeam() const;
		void removeVerticalSeam();
	private:
		void relaxVertical
			 (size_t, size_t, vector<double> &, vector<int> &) const;

		size_t H, V;
		vector<double> en;
};

#endif