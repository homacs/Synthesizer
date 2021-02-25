/*
 * SoundGeneratorSelector.h
 *
 *  Created on: 25 Feb 2021
 *      Author: homac
 */

#ifndef SOUNDGENERATORSELECTOR_H_
#define SOUNDGENERATORSELECTOR_H_


#include <vector>

#include "SineGenerator.h"
#include "SquareGenerator.h"
#include "SawtoothGenerator.h"
#include "TriangleGenerator.h"

class SoundGeneratorSelector {
	typedef std::vector<SoundGenerator*> generators_t;
	int cur;
	generators_t generators;

	SoundGeneratorSelector() {
		cur = 0;
		generators.push_back(new TriangleGenerator());
		generators.push_back(new SawtoothGenerator());
		generators.push_back(new SquareGenerator());
		generators.push_back(new SineGenerator());
		assert (generators.size() != 0);
	}
	virtual ~SoundGeneratorSelector() {
		for (generators_t::iterator it = generators.begin(); it != generators.end(); ++it)
		{
			delete (*it);
		}
	}


public:

	static SoundGeneratorSelector* instance;

	static void init() {
		instance = new SoundGeneratorSelector();
	}


	SoundGenerator* getNext() {

		SoundGenerator* gen =  generators[cur];
		int size = generators.size();
		cur = (cur + 1) % size;
		return gen;
	}


};

#endif /* SOUNDGENERATORSELECTOR_H_ */
