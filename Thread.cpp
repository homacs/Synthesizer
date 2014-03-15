/*
 * Thread.cpp
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#include "Thread.h"

#include <pthread.h>



void* __thread_start_routine(void* _instance) {
	Thread* instance = static_cast<Thread*>(_instance);
	// TODO: turn of timer handler for all threads per default
	instance->run();
	return NULL;
}

void Thread::start(void) {
	pthread_attr_t attr = {0};
	pthread_create(&pthread_ref, &attr, __thread_start_routine, static_cast<Thread*>(this));
}
