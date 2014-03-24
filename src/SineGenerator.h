/*
 * SineGenerator.h
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#ifndef SINEGENERATOR_H_
#define SINEGENERATOR_H_

#include <math.h>

#include "Block.h"
#include "Module.h"
#include "Note.h"
#include "NoteEvent.h"
#include "Report.h"
#include "Heap.h"


struct tone_t {
	block_time_t start;
	note_t freq;
};

static
int cmp_tone(tone_t* a, tone_t* b) {
	return a->freq - b->freq;
}

class SineGenerator : public Module {
	ConcurrentBlockQueue* output;
	NoteEventQueue* input;
	uint16_t amplification;
	bool active;
	block_time_t expected_block_time;
	block_time_t block_duration;
	Heap<tone_t> frequencies;
	Heap<tone_t> fadeout;
public:

	SineGenerator() : frequencies(16), fadeout(16) {
		output = 0;
		input = 0;
		active = true;
		amplification = -1;
		amplification /= 16;

		expected_block_time = 0;
		block_duration = Timer::instance.getBlockDuration();
	}

	void readInputs(block_time_t start, block_time_t end) {
		NoteEvent* e;
		assert(input);
		if (!input->size()) return;
		e = input->peek();
		if (e->getTime() < end) {
			input->pop();
			tone_t tone;
			tone.freq = e->getNote();
			tone.start = start;
			if (e->isStartNoteEvent()) { /* press event */
				frequencies.add(tone);
				Heap<tone_t>::iterator it = fadeout.find(tone, cmp_tone);
				if (it != fadeout.end()) fadeout.remove(it);
			} else { /* release event */
				Heap<tone_t>::iterator it = frequencies.find(tone, cmp_tone);
				if (it != frequencies.end()) {
					fadeout.add(*it);
					frequencies.remove(it);
				}
			}

			NoteEvent::release(e);
		}
	}

	int16_t close_to_zero(int16_t sample_value) {
		return sample_value > -10 && sample_value < 10;
	}

	int16_t getSampleValue(note_t frequency, block_time_t sample_time) {
		double periode_time = 1.0/frequency*1000000000; /*usecs per radiant*/

		double rad = double(sample_time)/periode_time*(2*M_PI);
		return sin(rad)*amplification + 0.5;
	}

	void process(void) {
		block_time_t block_time;
		do {
			block_time = Timer::instance.getCurrentBlockTime();
		} while (block_time < expected_block_time);



		if (expected_block_time && block_time != expected_block_time) {
			int missing = block_time - expected_block_time;

			Report::info("%d missing blocks\n", missing / block_duration);
		}
		block_time_t next_block_time = Timer::instance.getNextBlockTime(block_time);


		readInputs(block_time, next_block_time);

		Block* block = Block::create();
		block->timestamp = block_time;


		struct sample_t {
			int16_t left_channel;
			int16_t right_channel;
		};
		sample_t* sample = (sample_t*)block->data;
		sample_t* end = (sample_t*)(block->data + block->size);

		double sample_time;
		int num_samples = block->size / sizeof(sample_t);
		for (int i = 0; sample < end; i++, sample++) {
			sample_time = double(block_time) + (double(i)* block_duration) / num_samples ;
			int16_t sample_value = 0;

			Heap<tone_t>::iterator it;
			for (it = frequencies.begin(); it < frequencies.end(); it++) {
				sample_value += getSampleValue((it->freq) <<3, sample_time-it->start);
			}

			Heap<tone_t>::iterator end = fadeout.end();
			for (it = fadeout.begin(); it < end; it++) {
				int16_t v = getSampleValue((it->freq) <<3, sample_time-it->start);
				while (close_to_zero(v)) {
					fadeout.remove(it);
					end = fadeout.end();
					if (it == end) break;
					v = getSampleValue((it->freq) <<3, sample_time-it->start);
				}
				sample_value += v;
			}
			sample->right_channel = sample_value;
			sample->left_channel = sample_value;
		}

		assert(output);

		output->push(Block::reference(block));

		// release my own reference
		Block::release(block);
		expected_block_time = next_block_time;
	}

	void addOutput(ConcurrentBlockQueue* _output) {
		output = _output;
	}

	void addInput(NoteEventQueue* _input) {
		input = _input;
	}

};

#endif /* SINEGENERATOR_H_ */
