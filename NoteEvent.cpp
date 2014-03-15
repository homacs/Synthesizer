/*
 * NoteEvent.cpp
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#include "NoteEvent.h"
#include <vector>

template<class T>
class Pool : public std::vector<T*>{
public:
	T* get(void) {
		T* o;
		if (this->empty()) {
			o = new T;
		} else {
			o = this->back();
			this->pop_back();
		}
		return o;
	}

	void put(T* o) {
		this->push_back(o);
	}
};


Pool<NoteEvent> noteEventPool;



NoteEvent* NoteEvent::create(block_time_t t, note_t note, bool start) {
	NoteEvent* event = noteEventPool.get();
	event->init(t, note, start);
	return event;
}

void NoteEvent::init(block_time_t _t, note_t _note, bool _start) {
	Event::init(_t);
	note = _note;
	start = _start;
}


void NoteEvent::release(NoteEvent* event) {
	noteEventPool.put(event);
}
