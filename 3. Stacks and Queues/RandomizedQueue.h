#ifndef RANDOMIZED_QUEUE_H
#define RANDOMIZED_QUEUE_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <utility>

using std::allocator;
using std::cout;
using std::endl;
using std::ostream;
using std::for_each;
using std::initializer_list;
using std::mt19937;
using std::pair;
using std::size_t;

template <typename T> class RandomizedQueue;

template <typename T> 
ostream &print(ostream &, const RandomizedQueue<T> &);

template <typename T> class RandomizedQueue_iterator {
	friend class RandomizedQueue<T>;
	public:
		RandomizedQueue_iterator(const RandomizedQueue_iterator &rqi) {
			rq = rqi.rq;
			curr = rqi.curr;
		};
		RandomizedQueue_iterator &operator=
			(const RandomizedQueue_iterator &rqi) {
			rq = rqi.rq;
			curr = rqi.curr;
			return *this;
		};
		RandomizedQueue_iterator &next() { 
			++curr; 
			return *this; 
		};
		bool hasNext() { return curr < rq.size() - 1; };
		T &operator*() const { return *(rq.beg + curr); };
		T &operator->() const { return this->operator*(); };
		~RandomizedQueue_iterator() = default;
	private:		
		RandomizedQueue_iterator
			(const RandomizedQueue<T> &randQ, size_t pos):
			rq(randQ), curr(pos) { };		
		
		RandomizedQueue<T> rq;
		size_t curr;	
};

template <typename T>
class RandomizedQueue {
	friend class RandomizedQueue_iterator<T>;
	friend ostream &print<T>(ostream&, const RandomizedQueue<T>&); 	
	public:
		RandomizedQueue(): 
		beg(nullptr), fin(nullptr), cap(nullptr), mt_rand(time(0)) {};
		RandomizedQueue(const RandomizedQueue<T>&);
		RandomizedQueue(RandomizedQueue&&);
		RandomizedQueue<T> &operator=(const RandomizedQueue<T>&);
		RandomizedQueue<T> &operator=(RandomizedQueue<T>&&);
		void enqueue(const T&);
		T dequeue();
		T sample() { return size() ? *(beg + mt_rand() % size()) : T(); }
		RandomizedQueue_iterator<T> iterator();
		
		size_t size() const { return fin - beg;};
		size_t capacity() const { return cap - beg;};
		bool isEmpty() const { return size() == 0; };
		
		~RandomizedQueue();
	private:
		// utility functions
		void check_and_alloc();
		pair<T*, T*> alloc_and_copy(const T*, const T*);
		void reallocate();
		void free();	
		
		static allocator<T> alloc;
		T *beg;
		T *fin;
		T *cap;
		// random number generator
		mt19937 mt_rand;
};

template <typename T> 
allocator<T> RandomizedQueue<T>::alloc;

template <typename T> 
RandomizedQueue<T>::~RandomizedQueue() {
	free();
}

template<typename T>
RandomizedQueue<T>::RandomizedQueue(const RandomizedQueue<T> &rq) {	
	pair<T*, T*> p = alloc_and_copy(rq.beg, rq.fin);
	beg = p.first;
	fin = cap = p.second;
}

template<typename T>
RandomizedQueue<T>::RandomizedQueue(RandomizedQueue<T> &&rq): 
	beg(rq.beg), fin(rq.fin), cap(rq.cap) {
		rq.beg = rq.fin = rq.cap = nullptr;
}
	
template<typename T>
RandomizedQueue<T> &RandomizedQueue<T>::operator=
	(const RandomizedQueue<T> &rq) {
	pair<T*, T*> p = alloc_and_copy(rq.beg, rq.fin);
	free();
	beg = p.first;
	fin = cap = p.second;
	return *this;
}

template<typename T>
RandomizedQueue<T> &RandomizedQueue<T>::operator=
	(RandomizedQueue<T> &&rq) {
	if (this != &rq) {
		free();
		beg = rq.beg;
		fin = rq.fin;
		cap = rq.cap;
		rq.beg = rq.fin = rq.cap = nullptr;
	}
	return *this;
}

template <typename T>
void RandomizedQueue<T>::enqueue(const T &t) {	
	check_and_alloc();	
	alloc.construct(fin++, t);	
	size_t sz = size();
	size_t i = mt_rand() % sz;	
	T temp = *(beg + i);
	*(beg + i) = t;
	*(beg + sz - 1) = temp;		
}	

template <typename T> T RandomizedQueue<T>::dequeue() {
	T ret;
	if (beg != fin) {		
		--fin;		
		ret = *fin;
		size_t sz = size();
		if (beg + 4*sz <= cap) {
			for_each(beg + 2*sz, cap, [](T &t){ alloc.destroy(&t); });
			alloc.deallocate(beg + 2*sz, cap - beg - 2*sz);
			if (sz) 
				cap = beg + 2*sz - 1;
			else 
				beg = fin = cap = nullptr; 
		}			
	}
	return ret;
}

template <typename T>  
RandomizedQueue_iterator<T> RandomizedQueue<T>::iterator() {
	return RandomizedQueue_iterator<T>(*this, mt_rand() % size());
}

// utility functions
template <typename T>
void RandomizedQueue<T>::check_and_alloc() {
    if (fin == cap)
		reallocate();
  }

template <typename T>
pair<T*, T*> RandomizedQueue<T>::alloc_and_copy
	(const T *b, const T *e) {
    auto data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

template <typename T>
void RandomizedQueue<T>::reallocate() {	
    size_t n = (size() ? 2*size() : 1);	
	T *data = alloc.allocate(n);
	T *dest = data, *elem = beg;
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	beg = data;
	fin = dest;
	cap = beg + n;		
}

template <typename T>
void RandomizedQueue<T>::free() {	
    for_each(beg, fin, [](T &s){ alloc.destroy(&s); });
	alloc.deallocate(beg, cap - beg);					
}

// friend functions
template<typename T> 
ostream &print(ostream &os, const RandomizedQueue<T> &rq) {	
	for_each(rq.beg, rq.fin, [&os](const T &t){ os << t << " "; });
	return os;
}

#endif