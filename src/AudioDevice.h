/*
 * AudioDevice.h
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#ifndef AUDIODEVICE_H_
#define AUDIODEVICE_H_

#include <SDL2/SDL.h>

#include "BufferedStream.h"

class AudioDevice {
	AudioDevice(){
		input = 0;
		deviceId = 0;
		lower_bound = 0;
		upper_bound = 0;
	}
	friend void sdl_audio_device_callback(void* userdata, Uint8* stream, int size);

	BufferedStream* input;
	size_t lower_bound;
	size_t upper_bound;

	SDL_AudioSpec     spec;
	SDL_AudioDeviceID deviceId;

protected:
	void callback(uint8_t* stream, int size);

public:


	static AudioDevice instance;

	void init(int sample_frequency, int channels, int sample_size);
	void fini(void);

	void setInput(BufferedStream* _input) {
		input = _input;
	}
};

#endif /* AUDIODEVICE_H_ */
