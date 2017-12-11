/*
Statement of the problem:
Nuts and bolts. A disorganized carpenter has a mixed pile of n nuts and n bolts. 
The goal is to find the corresponding pairs of nuts and bolts. 
Each nut fits exactly one bolt and each bolt fits exactly one nut. 
By fitting a nut and a bolt together, the carpenter can see which one is bigger 
(but the carpenter cannot compare two nuts or two bolts directly). 
Design an algorithm for the problem that uses n log(n) compares (probabilistically).

Solution:
Pick an arbitrary nut and partition the bolts array by comparing each bolt with the chosen nut such that each bolt < nut is at the beginning of the array until the bolt that fits the nut, and each bolt > nut is at the end of the array after the bolt that fits the nut. 
Apply the same process to the array of nuts using the bolt that fits the nut that was originally chosen.
Repeat this process for the left and right subarrays separated by the (bolt, nut) pair that is put in place. 
Stop when the size of the subarray is 1.
*/

#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::swap;
using std::vector;

/*
Partition the vector a[] such that all elements with indices < k have values < pivot,
all elements with indices >= i have values > pivot,
and all elements with indices between k and i - 1 have values == pivot.
Return the pair of indices (k, i).
*/
pair<size_t, size_t> partition(vector<int> &a, size_t l, size_t r, int pivot) {	
	size_t i, j, k;
	// k -- all elements with indices < k have values < pivot
	// i -- all elements with indices between k and i - 1 have values == pivot
	// j -- all elements with indices > j have values > pivot
	i = k = l;
	j = r - 1;
	while (i <= j) {
		if (a[i] < pivot) 
			swap(a[i++], a[k++]);
		else {
			if (a[i] == pivot) 
				++i;
		 	else  // a[i] > pivot
				swap(a[i], a[j--]);
		}		
	}
	return pair<size_t, size_t>(k, i);
}

bool sortNB(vector<int> &a, vector<int> &b, size_t l, size_t r) {
	if (l >= r - 1) return true;
	// partition vector a[] using as pivot b[l]
	pair<size_t, size_t> pr1 = partition(a, l, r, b[l]);
	if (pr1.first == pr1.second)
		return false;
	// partition vector b[] using as pivot a[pr1.first]
	pair<size_t, size_t> pr2 = partition(b, l, r, a[pr1.first]);
	if ((pr1.first != pr2.first) || (pr1.second != pr2.second))
		return false;
	// sort the two remaining pieces
	return sortNB(a, b, l, pr1.first) && sortNB(a, b, pr1.second, r);
}

/*
Arrange the nuts and bolts such that they match.
Return true when this is possible and false otherwise.
*/
bool arrangeNB(vector<int> &a, vector<int> &b) {
	if (a.size() != b.size())
		return false;
	return sortNB(a, b, 0, a.size());
}

int main() {
	vector<int> nuts, bolts;
	
	nuts.push_back(5);
	nuts.push_back(2);
	nuts.push_back(8);
	nuts.push_back(5);
	nuts.push_back(9);
	nuts.push_back(3);
	nuts.push_back(1);
	
	bolts.push_back(5);
	bolts.push_back(9);
	bolts.push_back(2);
	bolts.push_back(8);
	bolts.push_back(5);
	bolts.push_back(1);
	bolts.push_back(3); 
	
	if (arrangeNB(nuts, bolts)) {
		cout << "Ordering of nuts: ";
		for (int x : nuts)
			cout << x << " ";
		cout << endl;
		cout << "Ordering of bolts: ";
		for (int x : bolts)
			cout << x << " ";
	} else
		cout << "The set of nuts and bolts cannot be matched perfectly" << endl;
}