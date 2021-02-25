/*
 * SawtoothGenerator.h
 *
 *  Created on: 25 Feb 2021
 *      Author: homac
 */

#ifndef SAWTOOTHGENERATOR_H_
#define SAWTOOTHGENERATOR_H_

#include "SoundGenerator.h"


/*
 *   /|
 *  / |
 * /  |
 *    |  /
 *    | /
 *    |/
 */

class SawtoothGenerator : public SoundGenerator {
public:
	SawtoothGenerator() {

	}
	virtual ~SawtoothGenerator() {

	}

	int16_t getSampleValue(note_t frequency, block_time_t sample_time) {
		block_time_t periode_time = period_time_usecs(frequency); /*usecs per oscillation*/
		double x = double(sample_time%periode_time)/periode_time; // x in [0,1]  position in single period
		double y; // y in [0,1]
		if (x < 0.5) {
			y = (+0.5 + x);
		} else {
			y = (-0.5 + x);
		}
		return y*amplification;
	}




};

#endif /* SAWTOOTHGENERATOR_H_ */
