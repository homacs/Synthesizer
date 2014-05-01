/*
 * WorkerThread.cpp
 *
 *  Created on: 15 Mar 2014
 *      Author: homac
 */

#include "WorkerThread.h"

void WorkerThread::run() {
	if (singleTaskWorker) {
		while (1) process(singleTask);
	}
}
