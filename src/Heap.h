/*
 * Heap.h
 *
 *  Created on: 10 Mar 2014
 *      Author: homac
 */

#ifndef HEAP_H_
#define HEAP_H_
#include <string.h>

template<class T>
int compare_value(T* a, T* b) {
	return memcmp(a,b,sizeof(T));
}

template<class T>
class Heap {
public:
	typedef T* iterator;
	typedef int (*compare_function_t)(T* a,T* b);
private:
	size_t capacity;
	size_t size;
	T* elems;
public:
	Heap(size_t _capacity) {
		capacity = _capacity;
		elems = new T[capacity];
		size = 0;
	}

	~Heap () {
		delete [] elems;
	}

	void add(T elem) {
		elems[size] = elem;
		size++;
	}

	iterator end() {
		return elems+size;
	}

	iterator begin() {
		return elems;
	}

	iterator find(T elem) {
		iterator it = elems;
		for (; it < end(); it++) {
			if (*it == elem) break;
		}
		return it;
	}

	iterator find(T elem, compare_function_t c) {
		iterator it = elems;
		for (; it < end(); it++) {
			if (!c(it, &elem)) break;
		}
		return it;
	}

	void remove(T elem) {
		iterator it = find(elem);
		if (it != end()) {
			remove(it);
		}
	}

	void remove(T* it) {
		size--;
		*it = *end();
	}

};

#endif /* HEAP_H_ */
