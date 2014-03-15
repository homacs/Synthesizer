/*
 * Keyboard.h
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "NoteEvent.h"

class KeyMap {
	note_t basenote;
public:
	KeyMap() : basenote(0) {}
	note_t getNote(int scancode);
};



class Keyboard {
	KeyMap keymap;
	NoteEventQueue output;
public:

	Keyboard() : output(1024) {}

	NoteEventQueue* getOutput() { return &output; }
	void pressed(int scancode);
	void released(int scancode);
};

#endif /* KEYBOARD_H_ */
