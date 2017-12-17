#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <algorithm>
//#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <ostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::greater;
using std::less;
using std::ostream;
using std::out_of_range;
using std::remove_reference;
using std::swap;
using std::vector;

template <typename T, typename Comparator> class PQ;

template <typename T, typename Comparator> 
ostream &print(ostream &, const PQ<T, Comparator> &);

template <typename RandomAccessIterator> 
void heapSort(RandomAccessIterator, RandomAccessIterator);

// the default (Comparator = less<T>) implements a max PQ
template <typename T, typename Comparator = less<T>>
class PQ {
	friend ostream &print<>(ostream &, const PQ &);
	
	template <typename RandomAccessIterator> 
	friend void heapSort(RandomAccessIterator, RandomAccessIterator);
		
	public:
		PQ(Comparator c = Comparator()): comp(c){ srand(time(0)); };
		void insert(const T&);
		void removeTop();
		size_t size() const { return a.size(); };
		bool empty() const { return a.empty(); };
		const T& top() const {
			if (size()) 
				return a[0];
			else
				throw out_of_range("Empty PQ");
		}
		const T& sample() const {
			if (size())  
				return a[rand() % size()];	
			else
				throw out_of_range("Empty PQ");
		};
		void delRandom();
	private:
		void swim(size_t); // bubble-up
		void sink(size_t); // bubble-down
		vector<T> a;
		Comparator comp;		
};

template <typename T, typename Comparator>
void PQ<T, Comparator>::insert(const T &key) {	
	a.push_back(key);
	swim(a.size() - 1);
}

template <typename T, typename Comparator>
void PQ<T, Comparator>::removeTop() {
	if (!a.size()) return; 
	swap(a[0], a[size() - 1]);
	a.pop_back();
	if (a.size())  
		sink(0);
}

template <typename T, typename Comparator>
void PQ<T, Comparator>::delRandom() {
	if (!size()) return;
	size_t i(rand() % size());
	swap(a[i], a[size() - 1]);
	a.pop_back();
	if (i && comp(a[(i-1)/2], a[i]))
		swim(i);
	else
		sink(i);
}

// helper functions
template <typename T, typename Comparator>
void PQ<T, Comparator>::swim(size_t i) {
	if (i >= a.size()) return;
	while (i && comp(a[(i-1)/2], a[i])) {
		swap(a[(i-1)/2], a[i]);
		i = (i - 1) / 2;
	}
}

template <typename T, typename Comparator>
void PQ<T, Comparator>::sink(size_t i) {
	size_t j = 2 * i + 2;
	while ((j < a.size()) && (comp(a[i], a[j-1]) || comp(a[i], a[j]))) {
		if (comp(a[j-1], a[j])) {
			swap(a[i], a[j]);
			i = j;
		} else {
			swap(a[i], a[j-1]);
			i = j - 1;
		}
		j = 2 * i + 2;	
	}
	j = 2 * i + 1;
	if ((j < a.size()) && comp(a[i], a[j]))
		swap(a[i], a[j]);
}

// friend functions
template <typename T, typename Comparator>
ostream &print(ostream &os, const PQ<T, Comparator> &pq) {
	for (const T t : pq.a)
	      os << t << " ";
	return os;
}

template <typename RandomAccessIterator> 
void heapSort(RandomAccessIterator b, RandomAccessIterator e) {
	typedef typename remove_reference<decltype(*b)>::type T;
	PQ<T> pq;
	// heapify bottom-up
	pq.a.resize(e - b);
	
	size_t i = pq.size();
	for (auto it = b; it != e; ++it) {
		pq.a[--i] = *it;
		pq.sink(i);
	}
	for (auto it = b; it != e; ++it) {
		*it = pq.a[0];
		pq.removeTop();
	}		
}

#endif