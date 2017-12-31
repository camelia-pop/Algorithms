#ifndef INDEX_PRIORITY_QUEUE_H
#define INDEX_PRIORITY_QUEUE_H

#include <functional>
#include <iostream>
#include <utility>

using std::endl;
using std::less;
using std::ostream;
using std::swap;

template <typename Key, typename Comparator> class IndexPQ;

template <typename Key, typename Comparator>
ostream &print(ostream &, const IndexPQ<Key, Comparator> &);

template <typename Key, typename Comparator = less<Key>>
class IndexPQ {
	friend ostream &print<>(ostream &, const IndexPQ &);
	public:
	    // n elements in PQ
		IndexPQ(int n = 0, Comparator c = Comparator()): 
		comp(c), N(n), qp(vector<int>(n, -1)), keys(vector<Key>(n)) {};
		inline bool contains(int) const;
		inline bool isEmpty() const;
		inline Key topKey() const;
		void insert(int, const Key &);
		int removeTop();
		void changeKey(int, const Key &);
		void deleteIndex(int);
	private:
		void swim(int);
		void sink(int);
		inline bool compIndex(int, int) const;
		void exchange(int, int);
		
		Comparator comp;
		int N;
		vector<int> pq;
		vector<int> qp;
		vector<Key> keys;
};

template <typename Key, typename Comparator>
bool IndexPQ<Key, Comparator>::contains(int i) const {
	return ((i >= 0) && (i < N) && (qp[i] != -1));
}

template <typename Key, typename Comparator>
bool IndexPQ<Key, Comparator>::isEmpty() const {
	return (pq.size() == 0);
}

// assumption: PQ is not empty
template <typename Key, typename Comparator>
Key IndexPQ<Key, Comparator>::topKey() const {
	return keys[pq[0]];
}

// if i was already inserted on PQ, we don't insert it again but we can change its key
template <typename Key, typename Comparator>
void IndexPQ<Key, Comparator>::insert(int i, const Key &key) {
	if ((i < 0) || (i >= N) || (qp[i] != -1)) return;
	pq.push_back(i);
	keys[i] = key;
	qp[i] = pq.size()-1;
	swim(pq.size()-1);
}

template <typename Key, typename Comparator>
int IndexPQ<Key, Comparator>::removeTop() {
	int v = pq[0];
	exchange(0, pq.size()-1);
	qp[pq[pq.size()-1]] = -1;
	pq.pop_back();
	sink(0);
	return v;
}

template <typename Key, typename Comparator>
void IndexPQ<Key, Comparator>::changeKey(int i, const Key &key) {
	if (!contains(i)) return;
	keys[i] = key;
	int j = qp[i];
	if (j && compIndex(j, (j-1)/2))
		swim(j);
	else
		sink(j);	
}

template <typename Key, typename Comparator>
void IndexPQ<Key, Comparator>::deleteIndex(int i) {
	int j = qp[i];
	exchange(j, pq.size()-1);
	qp[pq[pq.size()-1]] = -1;
	pq.pop_back();
	if (j && compIndex(j, (j-1)/2))
		swim(j);
	else
		sink(j);	
	
}

// helper functions
template <typename Key, typename Comparator>
void IndexPQ<Key, Comparator>::sink(int i) {
	if ((i < 0) || (i >= pq.size())) return;
	int j = 2 * i + 2;
	while ((j < pq.size()) && (compIndex(j-1, i) || comp(j, i))) {
		if (compIndex(j-1, j)) {
			exchange(i, j-1);
			i = j-1;
		} else {
			exchange(i, j);
			i = j;
		}
		j = 2 * i + 2;	
	}
	j = 2 * i + 1;
	if ((j < pq.size()) && compIndex(j, i))
		exchange(i, j);
}

template <typename Key, typename Comparator>
void IndexPQ<Key, Comparator>::swim(int i) {
	while (i && compIndex(i, (i-1)/2)) {
		exchange(i, (i-1)/2);
		i = (i - 1) / 2;
	}
}

template <typename Key, typename Comparator>
bool IndexPQ<Key, Comparator>::compIndex(int i, int j) const {
	return comp(keys[pq[i]], keys[pq[j]]);
};

template <typename Key, typename Comparator>
void IndexPQ<Key, Comparator>::exchange(int i, int j) {
	qp[pq[i]] = j;
	qp[pq[j]] = i;
	swap(pq[i], pq[j]);
}

// friend functions template <typename Key, typename Comparator = less<Key>>
template <typename Key, typename Comparator>
ostream &print(ostream &os, const IndexPQ<Key, Comparator> &ipq) {
	os << "Vector pq: ";
	for (int i = 0; i != ipq.pq.size(); ++i) os << ipq.pq[i] << " ";
	os << endl;
	os << "Vector qp: ";
	for (int i = 0; i != ipq.qp.size(); ++i) os << ipq.qp[i] << " ";
	os << endl;
	os << "Vector keys: ";
	for (int i = 0; i != ipq.keys.size(); ++i) os << ipq.keys[i] << " ";
	os << endl;
	return os;
}

#endif