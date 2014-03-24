/*
 * Keyboard.h
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "NoteEvent.h"

/** Simple mapping table mapping scancodes in notes
 */
class KeyMap {
	note_t basenote;
public:
	KeyMap() : basenote(0) {}
	note_t getNote(int scancode);
};


/** This is a very basic class which converts key events from the
 * PC keyboard into note events.
 *
 * The keyboard class is not driven by the audio processing engine
 * but by the GUI thread (see SDL main window).
 */
class Keyboard {
	KeyMap keymap;

	/** This is the output we will forward the translated notes to. */
	NoteEventQueue output;
public:

	Keyboard() : output(1024) {}

	NoteEventQueue* getOutput() { return &output; }
	void pressed(int scancode);
	void released(int scancode);
};

#endif /* KEYBOARD_H_ */
