/*
 * Timer.cpp
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

#include "Timer.h"
#include "Report.h"



Timer Timer::instance;
const int32_t Timer::max_output_delay_deviation = 50;

__thread bool main_thread;

void timer_handler(int sig, siginfo_t* siginfo, void* checkpoint) {
	if (main_thread) Timer::instance.update();
}

block_time_t Timer::getSystemTime (void) {
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	block_time_t result = t.tv_sec;
	result *= 1000;
	result += t.tv_nsec / 1000000;
	return result;
}
void Timer::synchronizeClock(void) {
	register block_time_t reported = block_time_t(double(reported_output_delay/100) +0.5) * 100;
	__sync_synchronize();
	if (reported != current_output_delay) {
		current_output_delay = reported;
		int64_t new_interval = standard_interval;
		double deviation = (double)current_output_delay - max_output_delay;
		if (deviation > 0) {
			// The timer of the audio device is running
			// slower then our virtual time.
			// We will slow down our timer to compensate it.
			//
			// We would like to adjust the virtual time to the audio device time
			// in about 10 secs
			const system_time_t adjustment_duration = 10000000;
			// The number of timer intervals in this duration will be
			const int adjustment_intervals = double(adjustment_duration) / standard_interval + 0.5;
			// the adjustment per interval
			// We want the adjustment even if its duration will be blow the 10 secs
			// Thus, we set the minimum to +1.
			uint32_t adjustment = (deviation / adjustment_intervals) + 1;

			new_interval += adjustment;
		}

		if (__builtin_expect(system_timer_config.it_interval.tv_usec != new_interval,0)) {
			// TODO: calculate the new system_timer_config.it_value considering the
			// reset and the time spend while calculating. Otherwise the first interval
			// will be <interval> + <processing time> long.
			const uint64_t processing_duration = 0;
			system_timer_config.it_interval.tv_usec = new_interval;
			system_timer_config.it_value.tv_usec = new_interval - processing_duration;
			assert(system_timer_config.it_interval.tv_usec > 0);
			if (setitimer(ITIMER_REAL, &system_timer_config, NULL)) {
				Report::sysfatal("setitimer");
			}
			Report::info("timer interval updated. delay: %05ld, interval: %05ld\n", current_output_delay, new_interval);
		}

	}
}
void Timer::update(void) {
	current_block += 1;
	__sync_synchronize();
	current_block_system_time.t = Timer::getSystemTime();

	synchronizeClock();

	current_block_time.t = (current_block+1)/2 * block_duration;
	__sync_synchronize();
	current_block += 1;
}


system_time_t Timer::getCurrentTimestamp(void) {
	system_time_t result;
	size_t block;
	do {
		block = current_block;
		while (block & 1) block = current_block;
		__sync_synchronize();
		system_time_t systime = Timer::getSystemTime();
		result = current_block_time.t + (systime - current_block_system_time.t) * system_timer_config.it_interval.tv_usec / block_duration;

	} while (block != current_block);

	return result;
}

block_time_t Timer::getBlockTime(block_time_t t) {
	return t / block_duration * block_duration;
}

block_time_t Timer::getCurrentBlockTime(void) {
	return current_block_time.t;
}
block_time_t Timer::getNextBlockTime(block_time_t t) {
	return t + block_duration;
}


void Timer::init(block_time_t _block_duration, block_time_t _clock_resolution /* micro seconds */, block_time_t _accepted_delay) {
	main_thread = true;
	block_duration = _block_duration;
	sample_duration = _clock_resolution;

	max_output_delay = _accepted_delay;
	current_output_delay = _accepted_delay;
	reported_output_delay = _accepted_delay;


	struct sigaction action = { 0 };

	action.sa_sigaction = timer_handler;

	if (sigaction(SIGALRM, &action, NULL)) {
		Report::sysfatal("sigaction");
	}


	if (block_duration >= 1000000) {
		Report::fatal("block duration too long");
	}

	standard_interval = block_duration % 1000000;

	system_timer_config.it_interval.tv_sec = 0;
	system_timer_config.it_interval.tv_usec = standard_interval;
	system_timer_config.it_value = system_timer_config.it_interval;
	struct itimerval check;

	if (setitimer(ITIMER_REAL, &system_timer_config, &check)) {
		Report::sysfatal("setitimer");
	}

	if (check.it_interval.tv_sec != 0 || check.it_interval.tv_usec != 0) {
		Report::fatal("another timer is already set!");
	}
}
