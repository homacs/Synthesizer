/*
 * TriangleGenerator.h
 *
 *  Created on: 25 Feb 2021
 *      Author: homac
 */

#ifndef TRIANGLEGENERATOR_H_
#define TRIANGLEGENERATOR_H_
#include "SoundGenerator.h"
/*    /\
 *   /  \
 *  /    \
 * /      \
 *         \      /
 *          \    /
 *           \  /
 *            \/
 */
class TriangleGenerator : public SoundGenerator {
public:
	TriangleGenerator();
	virtual ~TriangleGenerator();


	int16_t getSampleValue(note_t frequency, block_time_t sample_time) {
		block_time_t periode_time = period_time_usecs(frequency); /*usecs per oscillation*/
		double x = double(sample_time%periode_time)/periode_time; // x in [0,1]  position in single period
		double y; // y in [0,1]
		if (x < 0.25) {
			y = 0.5 + x*2;
		} else if (x < 0.75) {
			y = 1 - (x-0.25)*2;
		} else {
			y = (x - 0.75) * 2;
		}
		return y*amplification;
	}

};

#endif /* TRIANGLEGENERATOR_H_ */
