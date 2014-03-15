/*
 * main.cpp
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#include <SDL2/SDL.h>

#include "Keyboard.h"
#include "Synthesizer.h"
#include "Report.h"


/* Function Prototypes */
void PrintKeyInfo(SDL_KeyboardEvent *key);
void PrintModifiers(Uint16 mod);

/* main */
int main(int argc, char *argv[]) {
	Keyboard keyboard;
	SDL_Event event;
	bool quit = false;

	/* Initialise SDL */
	if (SDL_Init( SDL_INIT_VIDEO) < 0) {
		Report::fatal("Could not initialise SDL: %s\n", SDL_GetError());
	}



	/* Set a video mode */
	SDL_Window *screen = SDL_CreateWindow("Synthesizer",
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);

	if (!screen) {
		Report::fatal("Error opening window: %s\n", SDL_GetError());
	}

	Synthesizer::init(&keyboard);


	/* Loop until an SDL_QUIT event is found */
	while (!quit) {

		/* Poll for events */
		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			/* Keyboard event */
			/* Pass the event data onto PrintKeyInfo() */
			case SDL_KEYDOWN:
//				PrintKeyInfo(&event.key);
				if (!event.key.repeat) {
					keyboard.pressed(event.key.keysym.scancode);
				}
				break;
			case SDL_KEYUP:
//				PrintKeyInfo(&event.key);
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					quit = true;
				} else {
					if (!event.key.repeat) {
						keyboard.released(event.key.keysym.scancode);
					}
				}
				break;

				/* SDL_QUIT event (window close) */
			case SDL_QUIT:
				quit = true;
				break;

			default:
				break;
			}

		}

	}

	/* Clean up */
	SDL_Quit();
	exit(0);
}

/* Print all information about a key event */
void PrintKeyInfo(SDL_KeyboardEvent *key) {
	/* Is it a release or a press? */
	if (key->type == SDL_KEYUP)
		printf("Release:- ");
	else
		printf("Press:- ");

	/* Print the hardware scancode first */
	printf("Scancode: 0x%02X", key->keysym.scancode);
	/* Print the name of the key */
	printf(", Name: %s", SDL_GetKeyName(key->keysym.sym));
	/* We want to print the unicode info, but we need to make */
	/* sure its a press event first (remember, release events */
	/* don't have unicode info                                */
	if (key->type == SDL_KEYDOWN) {
		/* If the Unicode value is less than 0x80 then the    */
		/* unicode value can be used to get a printable       */
		/* representation of the key, using (char)unicode.    */
		printf(", Unicode: ");
		if (key->keysym.sym < 0x80 && key->keysym.sym > 0) {
			printf("%c (0x%04X)", (char) key->keysym.sym, key->keysym.sym);
		} else {
			printf("? (0x%04X)", key->keysym.sym);
		}
	}
	printf("\n");
	/* Print modifier info */
	PrintModifiers(key->keysym.mod);
}

/* Print modifier info */
void PrintModifiers(Uint16 mod) {
	printf("Modifiers: ");

	/* If there are none then say so and return */
	if (mod == KMOD_NONE) {
		printf("None\n");
		return;
	}

	/* Check for the presence of each SDLMod value */
	/* This looks messy, but there really isn't    */
	/* a clearer way.                              */
	if (mod & KMOD_NUM)
		printf("NUMLOCK ");
	if (mod & KMOD_CAPS)
		printf("CAPSLOCK ");
	if (mod & KMOD_LCTRL)
		printf("LCTRL ");
	if (mod & KMOD_RCTRL)
		printf("RCTRL ");
	if (mod & KMOD_RSHIFT)
		printf("RSHIFT ");
	if (mod & KMOD_LSHIFT)
		printf("LSHIFT ");
	if (mod & KMOD_RALT)
		printf("RALT ");
	if (mod & KMOD_LALT)
		printf("LALT ");
	if (mod & KMOD_CTRL)
		printf("CTRL ");
	if (mod & KMOD_SHIFT)
		printf("SHIFT ");
	if (mod & KMOD_ALT)
		printf("ALT ");
	printf("\n");
}
