#ifndef MEDIAN_H
#define MEDIAN_H

#include "PQ.h"
#include <functional>
#include <ostream>
#include <stdexcept>

using std::endl;
using std::less;
using std::ostream;
using std::out_of_range;

template <typename T, typename Comparator> class Median;

template <typename T, typename Comparator>
ostream &print(ostream &, const Median<T, Comparator> &);

// helper class for the class Median
template <typename T, typename Comparator>
class ComplementComparator {
	public:
		bool operator()(const T &x, const T &y) { 
			return ! Comparator()(x, y); 
		};
};

template <typename T, typename Comparator = less<T>>
class Median {
	friend ostream &print<>(ostream &, const Median &);
	public:
		void insert(const T&);
		void removeMed();
		T median() const {
			// in the computation of the average, the result will be int if T = int
			if (low.empty())
				throw out_of_range("No elements");
			return (low.size() == high.size()) ? 
			        (low.top() + high.top()) / 2 :
					low.top();
		};
	private:
		PQ<T, Comparator> low;
		PQ<T, ComplementComparator<T, Comparator>> high;
};

template <typename T, typename Comparator>
void Median<T, Comparator>::insert(const T &val) {
	if (!low.size()) {
		low.insert(val);
		return;
	}
	
	(val < median()) ? low.insert(val) : high.insert(val);
	
	if (low.size() == high.size() + 2) {
		high.insert(low.top());
		low.removeTop();		
	} else 
		if (high.size() == low.size() + 1) {
			low.insert(high.top());
			high.removeTop();
		}
}

template <typename T, typename Comparator>
void Median<T, Comparator>::removeMed() {
	if (!low.size())
		return;
	if (low.size() > high.size())
		low.removeTop();
	else 
		high.removeTop();		
}

// friend function
template <typename T, typename Comparator>
ostream &print(ostream &os, const Median<T, Comparator> &med) {
	os << "Left priority queue: ";
	print(os, med.low) << endl;
	os << "Right priority queue: ";
	print(os, med.high);
	return os;	
}

#endif