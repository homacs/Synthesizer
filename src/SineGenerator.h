/*
 * SineGenerator.h
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#ifndef SINEGENERATOR_H_
#define SINEGENERATOR_H_

#include "SoundGenerator.h"

class SineGenerator : public SoundGenerator {
public:

	SineGenerator() : SoundGenerator() {
	}


	int16_t getSampleValue(note_t frequency, block_time_t sample_time) {
		block_time_t periode_time = period_time_usecs(frequency); /*usecs per oscillation*/

		double rad = double(sample_time%periode_time)/periode_time*(2*M_PI);
		return sin(rad)*amplification + 0.5;
	}


};

#endif /* SINEGENERATOR_H_ */
