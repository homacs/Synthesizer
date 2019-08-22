/*
 * Keyboard.h
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "NoteEvent.h"


/** Simple mapping table mapping scancodes to notes
 */
class KeyMap {

	struct map_elem_t {
		int scancode;
		note_t note;
	};
	static map_elem_t STANDARD_MAP [];
private:
	static const unsigned int MAX_OCTAVE_SHIFT = 8;
	static const unsigned int MIN_OCTAVE_SHIFT = 1;

	unsigned int octave_shift;
	struct map_elem_t* map;
public:
	KeyMap();
	~KeyMap();
	note_t getNote(int scancode);
	void octave_inc();
	void octave_dec();
};


/** This is a very basic class which converts key events from the
 * PC keyboard into note events.
 *
 * The keyboard class is not driven by the audio processing engine
 * but by the GUI thread (see SDL main window).
 */
class Keyboard {
	KeyMap keymap;

	/** This is the sink we will forward the translated notes to. */
	NoteEventQueue output;
public:

	Keyboard() : output(1024) {}

	NoteEventQueue* getOutput() { return &output; }
	void pressed(int scancode);
	void released(int scancode);
};

#endif /* KEYBOARD_H_ */
