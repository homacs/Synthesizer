/*
 * ConcurrentQueue.h
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#ifndef CONCURRENTQUEUE_H_
#define CONCURRENTQUEUE_H_



#include <stdint.h>
#include <stdlib.h>
#include <assert.h>


template<class T>
class ConcurrentQueue {
	size_t capacity;
	T* queue;
	volatile size_t first;
	volatile size_t last;
	ConcurrentQueue(){capacity = 0; queue = 0; first = 0; last = 0;};
public:
	ConcurrentQueue(size_t _capacity) {
		capacity = _capacity;

		queue = new T[capacity];
		clear();
	}
	~ConcurrentQueue() {
		delete [] queue;
	}
	void clear (void) {
		first = 0;
		last = 0;
	}

	size_t size(void) {
		size_t result = (last + capacity - first) % capacity;
		return result;
	}

	T pop(void) {
		int current = first;
		while (first == last) __sync_synchronize();

		first = (first + 1) % capacity;

		assert(first >= 0 && first < capacity);

		return queue[current];
	}

	void push(T elem) {
		assert(size() < capacity);
		queue[last] = elem;
		size_t next_last = (last + 1) % capacity;
		while (next_last == first) __sync_synchronize();
		last = next_last;

		assert(last >= 0 && last < capacity);
	}

	T peek(void) {
		return queue[first];
	}
};


#endif /* CONCURRENTQUEUE_H_ */
