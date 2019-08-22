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


static const int16_t VOLUME_MAX = 1000;

struct tone_t {
	block_time_t start;
	note_t freq;
	int16_t volume;
	block_time_t decay;
	block_time_t decay_start;
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
			tone.volume = VOLUME_MAX;
			tone.decay = 3000000;
			tone.freq = e->getNote();
			tone.start = start;
			if (e->isStartNoteEvent()) { /* press event */
				frequencies.add(tone);
				Heap<tone_t>::iterator it = fadeout.find(tone, cmp_tone);
				if (it != fadeout.end()) fadeout.remove(it);
			} else { /* release event */
				Heap<tone_t>::iterator it = frequencies.find(tone, cmp_tone);
				if (it != frequencies.end()) {
					it->decay_start = start;
					fadeout.add(*it);
					frequencies.remove(it);
				}
			}

			NoteEvent::release(e);
		}
	}

	int16_t getDecayVolume (tone_t* tone, block_time_t sample_time) {
		double v = 1.0f - (double)(sample_time - tone->decay_start)/tone->decay;
		if (v <= 0) return 0;
		else return v * tone->volume;
	}

	int16_t getSampleValue(note_t frequency, block_time_t sample_time) {
		double periode_time = 1000000000.0/frequency; /*usecs per radiant*/

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
				int16_t v = getSampleValue((it->freq), sample_time - it->start);
				sample_value += v * (float)(it->volume)/VOLUME_MAX;
			}

			Heap<tone_t>::iterator end = fadeout.end();
			for (it = fadeout.begin(); it < end; it++) {
				int16_t volume = getDecayVolume(it, sample_time);
				while (volume == 0) {
					fadeout.remove(it);
					end = fadeout.end();
					if (it == end) goto end_loop;
					volume = getDecayVolume(it, sample_time);
				}
				int16_t v = getSampleValue((it->freq), sample_time - it->start);
				sample_value += v * (float)(volume)/VOLUME_MAX;
			}
			end_loop:
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
