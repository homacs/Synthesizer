/*
 * Module.h
 *
 *  Created on: 15 Mar 2014
 *      Author: homac
 */

#ifndef MODULE_H_
#define MODULE_H_

class Module {
protected:
	Module(){}
	virtual ~Module(){}


public:
	virtual void process(void) = 0;
};

#endif /* MODULE_H_ */
