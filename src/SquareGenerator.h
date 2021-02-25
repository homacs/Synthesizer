/*
 * SquareGenerator.h
 *
 *  Created on: 25 Feb 2021
 *      Author: homac
 */

#ifndef SQUAREGENERATOR_H_
#define SQUAREGENERATOR_H_

#include "SoundGenerator.h"

class SquareGenerator: public SoundGenerator {
public:
	SquareGenerator(){}
	virtual ~SquareGenerator(){}


	int16_t getSampleValue(note_t frequency, block_time_t sample_time) {
		block_time_t periode_time = period_time_usecs(frequency); /*usecs per oscillation*/
		double x = double(sample_time%periode_time)/periode_time; // x in [0,1]  position in single period
		double y; // y in [0,1]
		if (x < 0.5) {
			y = 0;
		} else {
			y = 1;
		}
		return y*amplification;
	}

};

#endif /* SQUAREGENERATOR_H_ */
