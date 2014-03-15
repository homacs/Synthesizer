/*
 * Keyboard.cpp
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */


#include <stdio.h>

#include "Keyboard.h"
#include "Timer.h"
#include "NoteEvent.h"
#include "Report.h"


void Keyboard::pressed(int scancode) {
	block_time_t t = Timer::instance.getCurrentTimestamp();
	note_t note = keymap.getNote(scancode);

	if (note == NOTE_UNDEFINED) return;

	NoteEvent* event = NoteEvent::create(t, note, true);
	printf("start %d\n", note);
	output.push(event);
}

void Keyboard::released(int scancode) {
	block_time_t t = Timer::instance.getCurrentTimestamp();
	note_t note = keymap.getNote(scancode);

	if (note == NOTE_UNDEFINED) return;

	NoteEvent* event = NoteEvent::create(t, note, false);
	printf("release %d\n", note);

	output.push(event);
}


struct map_elem_t {
	int scancode;
	note_t note;
};


map_elem_t map[] = {
		{ 0x1D, NOTE_C0},
		{ 0x16, NOTE_Cis0},
		{ 0x1B, NOTE_D0},
		{ 0x07, NOTE_Dis0},
		{ 0x06, NOTE_E0},
		{ 0x19, NOTE_F0},
		{ 0x0A, NOTE_Fis0},
		{ 0x05, NOTE_G0},
		{ 0x0B, NOTE_Gis0},
		{ 0x11, NOTE_A0},
		{ 0x0D, NOTE_B0},
		{ 0x10, NOTE_H0},

		{ 0x36, NOTE_C1},
		{ 0x0f, NOTE_Cis1},
		{ 0x37, NOTE_D1},
		{ 0x33, NOTE_Dis1},
		{ 0x38, NOTE_E1},
		{ 0xe5, NOTE_F1},
		{ 0x14, NOTE_F1},
		{ 0x1f, NOTE_Fis1},
		{ 0x1a, NOTE_G1},
		{ 0x20, NOTE_Gis1},
		{ 0x08, NOTE_A1},
		{ 0x21, NOTE_B1},
		{ 0x15, NOTE_H1},

		{ 0x17, NOTE_C2},
		{ 0x23, NOTE_Cis2},
		{ 0x1c, NOTE_D2},
		{ 0x24, NOTE_Dis2},
		{ 0x18, NOTE_E2},
		{ 0x0c, NOTE_F2},
		{ 0x26, NOTE_Fis2},
		{ 0x12, NOTE_G2},
		{ 0x27, NOTE_Gis2},
		{ 0x13, NOTE_A2},
		{ 0x2d, NOTE_B2},
		{ 0x2f, NOTE_H2},

		{ 0x30, NOTE_C3},

		{ 0,    NOTE_UNDEFINED} /* marking last entry too! */
};


note_t KeyMap::getNote(int scancode) {

	// TODO: use binary search over scancodes, or build direct lookup table

	Report::info("scancode: 0x%02x\n");
	int i;
	for (i = 0; map[i].note; i++) {
		if (map[i].scancode == scancode) break;
	}

	return map[i].note;
}
