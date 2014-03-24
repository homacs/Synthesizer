/*
 * WorkerThread.h
 *
 *  Created on: 15 Mar 2014
 *      Author: homac
 */

#ifndef WORKERTHREAD_H_
#define WORKERTHREAD_H_

#include "Thread.h"
#include "Task.h"


class WorkerThread : public Thread {
private:
	bool singleTaskWorker;
	task_t singleTask;
public:
	WorkerThread(task_t t) {
		singleTaskWorker = true;
		singleTask = t;
	}

	virtual ~WorkerThread() {}

	void process(task_t task) {
		task.module->process();
	}

	void run();
};

#endif /* WORKERTHREAD_H_ */
