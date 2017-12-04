#ifndef QUEUE_WITH_STACKS_H
#define QUEUE_WITH_STACKS_H

#include <iostream>
#include <stack>
#include <stdexcept>

using std::runtime_error;
using std::stack;

template <typename T>
class QueueWithStacks {
	public:
		typedef T value_type;
		typedef typename stack<T>::size_type size_type;
	
		QueueWithStacks() = default;
		bool empty() const { return st1.empty(); };
		typename stack<T>::size_type size() const { return st1.size(); };
		void push(const T &t) { st1.push(t); };
		template <typename... Args>
		void emplace(Args&&... args) { 
			st1.emplace(std::forward<Args>(args)...); 
		};
		void pop();
		value_type& front();
		const value_type& front() const;
		value_type& back() { return st1.top(); };
		const value_type& back() const { return st1.top(); };
	private:
		stack<T> st1, st2;
};

template <typename T>
void QueueWithStacks<T>::pop() {
	if (st1.empty()) return;
	T t;
	while (!st1.empty()) {
		t = st1.top();
		st1.pop();
		st2.push(t);
	}
	st2.pop();
	while (!st2.empty()) {
		t = st2.top();
		st2.pop();
		st1.push(t);
	}
}

template <typename T>
typename QueueWithStacks<T>::value_type& QueueWithStacks<T>::front() {
	if (st1.empty())
		throw runtime_error("Empty queue");
	T t1;
	while (!st1.empty()) {
		T t1 = st1.top();
		st1.pop();
		st2.push(t1);
	}
	T t2 = st2.top();
	st2.pop();
	st1.push(t2);
	T &t = st1.top();
	while (!st2.empty()) {
		t2 = st2.top();
		st2.pop();
		st1.push(t2);
	}
	return t;
}

template <typename T>
const typename QueueWithStacks<T>::value_type& 
	QueueWithStacks<T>::front() const {
	if (st1.empty())
		throw runtime_error("Empty queue");
	T t1;
	while (!st1.empty()) {
		T t1 = st1.top();
		st1.pop();
		st2.push(t1);
	}
	T t2 = st2.top();
	st2.pop();
	st1.push(t2);
	const T &t = st1.top();
	while (!st2.empty()) {
		t2 = st2.top();
		st2.pop();
		st1.push(t2);
	}
	return t;
}

#endif