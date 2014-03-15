/*
 * AudioDevice.cpp
 *
 *  Created on: 9 Mar 2014
 *      Author: homac
 */

#include <SDL2/SDL.h>
#include <assert.h>


#include "AudioDevice.h"
#include "Report.h"
#include "Timer.h"

#define SDL_AUDIO_OUTPUT 0
#define SDL_AUDIO_INPUT 1
#define SDL_AUDIO_PAUSE_OFF 0
#define SDL_AUDIO_PAUSE_ON 1

void sdl_audio_device_callback(void* userdata, Uint8* stream, int size) {
	AudioDevice* device = (AudioDevice*)userdata;
	device->callback(stream, size);
}

AudioDevice AudioDevice::instance;

void AudioDevice::init(int sample_frequency, int channels, int sample_size) {

	lower_bound = 2;
	upper_bound = 4;

	deviceId = 0;

	spec.callback = sdl_audio_device_callback;
	spec.channels = channels;
	// TODO: consider sample size
	spec.format = AUDIO_S16LSB;
	spec.freq = sample_frequency;
	spec.padding = 0;
	spec.samples = 0; 	    /* buffer size in samples */
	spec.silence = 0;
	spec.size =    0;       /* buffer size in bytes (calculated) */
	spec.userdata = &instance;

	assert(!SDL_AUDIO_ISFLOAT(spec.format));

	if (0 != SDL_Init(SDL_INIT_AUDIO)) {
		Report::fatal("Initialisation failed");
	}

	const char* driver_name = "pulseaudio";
	if (SDL_AudioInit(driver_name)) {
		Report::fatal("Audio driver failed to initialize: %s\n", driver_name);
	}

	deviceId = SDL_OpenAudioDevice(NULL, SDL_AUDIO_OUTPUT, &spec, NULL,
			0 /* do not open if spec is not met */);
	if (deviceId == 0) {
		Report::fatal("Failed to open audio: %s\n", SDL_GetError());
	}

	SDL_PauseAudioDevice(deviceId, SDL_AUDIO_PAUSE_OFF);  // start audio playing.
}


void AudioDevice::fini(void) {
	SDL_CloseAudioDevice(deviceId);
}


void dumpStream (uint8_t* stream, int size) {
	struct sample_t {
		int16_t left;
		int16_t right;
	};
	sample_t* it = (sample_t*)stream;
	size = size / sizeof(sample_t);
	for (int i = 0; i < size; i++) {
		printf("%07d\n", it->left);
		it++;
	}
}
void AudioDevice::callback(uint8_t* stream, int size) {
	block_time_t timestamp = 0;
	if (input) {
		timestamp = input->read(stream, size);
	} else {
		memset(stream, 0, size);
	}
	Timer::instance.reportBlockOutput(timestamp);
}
