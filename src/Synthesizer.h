/*
 * Synthesizer.h
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#ifndef SYNTHESIZER_H_
#define SYNTHESIZER_H_
#include "Keyboard.h"

#include "SoundGeneratorSelector.h"


class Synthesizer {


public:
	static void init(Keyboard* keyboard);
	static void nextGenerator();
};

#endif /* SYNTHESIZER_H_ */
