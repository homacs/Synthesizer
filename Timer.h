/*
 * Timer.h
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include <signal.h>
#include <sys/time.h>
#include <math.h>

#include "Report.h"

typedef uint64_t block_time_t;
typedef block_time_t system_time_t;

typedef struct  {
	__attribute__((aligned(16)))
	volatile block_time_t t;
	uint8_t space[48];
} concurrent_block_time_t;

typedef struct  {
	__attribute__((aligned(16)))
	volatile system_time_t t;
	uint8_t space[48];
} concurrent_system_time_t;



class Timer {

	friend void timer_handler(int sig, siginfo_t* siginfo, void* checkpoint);

	block_time_t block_duration;

	block_time_t sample_duration;

	volatile size_t current_block;

	volatile concurrent_system_time_t current_block_system_time;

	volatile concurrent_block_time_t current_block_time;

	struct itimerval system_timer_config;

	int64_t standard_interval;
	static const int32_t max_output_delay_deviation;

	void update(void);
	void synchronizeClock(void);

	block_time_t max_output_delay;
	block_time_t current_output_delay;
	block_time_t reported_output_delay;
public:
	static Timer instance;


	void init(block_time_t block_duration /* microseconds */, block_time_t resolution /* micro seconds */, block_time_t _accepted_delay /* micro seconds */);

	block_time_t getCurrentTimestamp(void);

	block_time_t getBlockTime(block_time_t t);
	block_time_t getNextBlockTime(block_time_t t);
	block_time_t getSampleDuration() {
		return sample_duration;
	}
	block_time_t getBlockDuration() {
		return block_duration;
	}

	block_time_t getCurrentBlockTime(void);

	/** -1 to speed up
	 *  +1 to slow down
	 */
	void reportBlockOutput(block_time_t time_of_block) {
		if (time_of_block <= 0) return;
		double delay = getCurrentTimestamp() - time_of_block;
		double sliding_avg_window_size = 200.0-1;
		delay = (delay + reported_output_delay * sliding_avg_window_size)/(sliding_avg_window_size+1);
		reported_output_delay = delay;
		Report::info("avg output delay: %05f\r", delay);
	}



	static system_time_t getSystemTime(void);



};

#endif /* TIMER_H_ */
