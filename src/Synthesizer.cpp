/*
 * Synthesizer.cpp
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "Report.h"
#include "Timer.h"
#include "Synthesizer.h"
#include "AudioDevice.h"
#include "SineGenerator.h"
#include "Task.h"
#include "WorkerThread.h"

size_t 	align_to_power_of_2(size_t value) {
	size_t result = 0;
	if (value) {
		result = 1;
		value = value >> 1;
		while (value) {
			result = result << 1;
			value = value >> 1;
		}
	}
	return result;
}


void Synthesizer::init(Keyboard* keyboard) {


	uint32_t sample_frequency = 44100; /**hertz */
	int channels = 2;
	int sample_bit_size = 16; /* bits */
	int max_output_delay = 10;/* milliseconds */
	int max_processing = 6; /* milliseconds */


	/* The block size is a fixed value for the whole runtime of the system.
	 * It is calculated considering the maximum output delay accepted by the user
	 * and the expected maximum processing time required by the system for the
	 * generation of one block and its forwarding to the audio device. */
	size_t block_size = (max_output_delay - max_processing) * channels * sample_bit_size * sample_frequency / 8 / 1000; /*bytes*/
	block_size = block_size &~ 63UL;

	if (!block_size) {
		Report::fatal("requested maximum output delay too tight!\n");
	}

	Report::info("block_size: %d [bytes]\n", block_size);

	int samples_per_block = block_size * 8 / sample_bit_size / channels;

	Report::info("samples per block: %d\n", samples_per_block);

	 /* The block duration is truncated and therefore lower than the amount of samples
	  * at the given frequency would mean in real time. This means, the internal clock
	  * will always run a little bit faster than the clock of the audio device. But the
	  * clock synchronises against the audio device and slows down from time to time to
	  * compensate the deviation.
	  * */
	block_time_t block_duration = (1000000*samples_per_block)/sample_frequency;

	Report::info("block_duration: %d [us]\n", block_duration);

	/* highest possible input resolution at 44khz is 1/44000 = */
	uint32_t resolution = 1000000/sample_frequency; /* us */

	BlockPool::init(block_size);

	Timer::instance.init(block_duration, resolution, max_output_delay * 1000);

	AudioDevice::instance.init(sample_frequency, channels, sample_bit_size);

	SineGenerator* sineGenerator = new SineGenerator();
	sineGenerator->addInput(keyboard->getOutput());
	BufferedStream* link = new BufferedStream(1024);
	AudioDevice::instance.setInput(link);
	sineGenerator->addOutput(link->getInput());
	task_t t;
	t.module = sineGenerator;
	WorkerThread* thread = new WorkerThread(t);

	thread->start();
}
