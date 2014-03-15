/*
 * Event.h
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#ifndef EVENT_H_
#define EVENT_H_


#include "Timer.h"

class Event {
	block_time_t t;
public:
	block_time_t getTime() { return t; }
	void init(block_time_t t);
};

#endif /* EVENT_H_ */
