/*
 * Module.h
 *
 *  Created on: 15 Mar 2014
 *      Author: homac
 */

#ifndef MODULE_H_
#define MODULE_H_


/** Base class for modules driven by the threads of the
 * audio processing engine. */
class Module {
	/* TODO: design a standard input output processing procedure */
protected:
	Module(){}
	virtual ~Module(){}


public:
	/** The method called by a thread of the audio processing engine.
	 * Its task is to process the inputs of the module for the given
	 * time frame into output data (e.g. Blocks of the audio stream
	 * and output values/events and such).
	 */
	virtual void process(void) = 0;
};

#endif /* MODULE_H_ */
