#ifndef STACK_WITH_MAX_H
#define STACK_WITH_MAX_H

#include <iostream>
#include <deque>
#include <stdexcept>

using std::runtime_error;
using std::deque;

template <typename T>
class StackWithMax {
	public:
		typedef T value_type;
		typedef typename deque<T>::size_type size_type;
	
		StackWithMax() = default;
		bool empty() const { return deq.empty(); };
		typename deque<T>::size_type size() const { return deq.size(); };
		void push(const T &t) { 
			deq.push_front(t); 
			if (deqMax.empty() || (t >= deqMax.front())) 
				deqMax.push_front(t);
		};
		void pop() {
			if (deq.front() == deqMax.front())	
				deqMax.pop_front();
			deq.pop_front(); 
		};
		value_type max() const { 
			if (deqMax.empty())
				throw runtime_error("Empty stack");
			return deqMax.front(); 
		};
		value_type& top() { 
			if (deq.empty())
				throw runtime_error("Empty stack");
			return deq.front();
		};
		const value_type& front() const { 
			if (deq.empty())
				throw runtime_error("Empty stack");
			return deq.front();
		};
		value_type& back() { 
			if (deq.empty())
				throw runtime_error("Empty stack");
			return deq.back();
		};
		const value_type& back() const { 
			if (deq.empty())
				throw runtime_error("Empty stack");
			return deq.back();
		};
	private:
		deque<T> deq, deqMax;
};

#endif