/*
 * Thread.h
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>


class Thread {
	friend void* __thread_start_routine(void* _instance);


	pthread_t pthread_ref;

protected:
	/**
	 * "Main" method called by the instantiated thread.
	 */
	virtual void run(void) = 0;

	virtual ~Thread() {}

public:
	Thread() {
		pthread_ref = 0;
	}
	void start(void);


};



#endif /* THREAD_H_ */
