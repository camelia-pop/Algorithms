/*
Statement of the problem:
2-sum. Given an array a[] of N 64-bit integers and a target value T, determine whether there are two distinct integers i and j such that a[i] + a[j] = T. Your algorithm should run in linear time in the worst case.

Solution:
View the integers as strings consisting of characters 0 and 1 (L = 2). The size of each string is W = 64. Order them increasingly using least significant digit (LSD) radix sort. Then traverse the ordered array with index i starting from 0 and index j starting from a.size() - 1.
If a[i] + a[j] < T, increase i by 1.
If a[i] + a[j] > T, decrease j by 1. 
Stop when i == j or a[i] + a[j] == T.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::swap;
using std::vector;

// convert a vector of integers to their binary representation
vector<string> int_to_binary(const vector<int> &a, size_t W) {
	vector<string> a_binary(a.size());
	for (size_t i = 0; i != a.size(); ++i) {
		int n = a[i];
		while (n) {
			if (n % 2)
				a_binary[i].push_back('1');
			else
				a_binary[i].push_back('0');
			n = (n - n % 2) / 2;
		}
		if (n < W)
			a_binary[i] = a_binary[i] + string(W - a_binary[i].size(), '0');
		for (size_t j = 0; j != W / 2; ++j)
			swap(a_binary[i][j], a_binary[i][W - j - 1]);
	}
	return a_binary;
}

void LSD_radix_sort
	(vector<string> &a_binary, vector<string> &aux_binary,
	 vector<int> &a, vector<int> &aux, size_t L, int d) {
	vector<int> count(L + 1, 0);
	for (size_t i = 0; i != a_binary.size(); ++i)
		++count[a_binary[i][d] - '0' + 1];
	for (size_t i = 0; i != L; ++i)
		count[i + 1] += count[i];
	for (size_t i = 0; i != a_binary.size(); ++i) {
		aux_binary[count[a_binary[i][d] - '0']] = a_binary[i];
		aux[count[a_binary[i][d] - '0']] = a[i];
		++count[a_binary[i][d] - '0'];
	}
	for (size_t i = 0; i != a_binary.size(); ++i) {
		a_binary[i] = aux_binary[i];
		a[i] = aux[i];
	}
}

void LSD_radix_sort(vector<int> &a, size_t W) {
	vector<string> aux_binary(a.size());
	vector<string> a_binary = int_to_binary(a, W);
	vector<int> aux(a.size());
	for (int d = W - 1; d >= 0; --d) 
		LSD_radix_sort(a_binary, aux_binary, a, aux, 2, d);	
}

bool two_sum_exists(vector<int> a, int T, size_t W) {
	LSD_radix_sort(a, W);
	size_t i = 0, j = a.size() - 1;
	while (i < j) 
		if (a[i] + a[j] < T)
			++i;
		else 
			if (a[i] + a[j] > T)
				--j;
			else
				return true;
	return false;		
}

int main() {
	ifstream is("integers.txt");
	int n, T;
	vector<int> a;
	is >> T;
	while (is >> n) 
		a.push_back(n);
	is.close();
	
	cout << "Sum = " << T << endl;
	cout << "Vector a: ";
	for (size_t i = 0; i != a.size(); ++i)
		cout << a[i] << " ";
	cout << endl;
	int W = 64;
	cout << "2SUM exists? " << two_sum_exists(a, T, W) << endl;
}

