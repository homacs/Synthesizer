/*
 * NoteEvent.h
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#ifndef NOTEEVENT_H_
#define NOTEEVENT_H_


#include "Note.h"
#include "Timer.h"
#include "Event.h"

#include "ConcurrentQueue.h"


class NoteEvent : public Event {

	note_t note;
	bool start;

protected:
	void init(block_time_t t, note_t note, bool start);
public:

	bool isStartNoteEvent() {return start;}
	note_t getNote() { return note; }

	static NoteEvent* create(block_time_t t, note_t note, bool start);
	static void release(NoteEvent* event);
};


typedef ConcurrentQueue<NoteEvent*> NoteEventQueue;

#endif /* NOTEEVENT_H_ */
