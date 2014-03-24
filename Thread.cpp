/*
 * Thread.cpp
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#include "Thread.h"
#include "Report.h"

void* __thread_start_routine(void* _instance) {
	Thread* instance = static_cast<Thread*>(_instance);

	//
	// now we are inside the new thread.
	// here we can do some framework related initialisation.
	//

	// turn of timer handler for all threads per default
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGVTALRM);
	sigaddset(&set, SIGALRM);
	if (pthread_sigmask(SIG_BLOCK, &set, NULL)) {
		 Report::fatal("could not set standard signal mask for the worker thread.");
	}

	// enter the application level code
	instance->run();

	// not joinable, no return
	return NULL;
}

void Thread::start(void) {
	pthread_create(&pthread_ref, NULL /* standard attributes only */, __thread_start_routine, static_cast<Thread*>(this));
}


