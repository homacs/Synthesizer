/*
 * Noteh
 *
 *  Created on: 8 Mar 2014
 *      Author: homac
 */

#ifndef NOTE_H_
#define NOTE_H_

#include <stdint.h>



typedef uint32_t frequency_t; /* oscillations per 1000 seconds */


typedef frequency_t note_t;

#define NOTE_UNDEFINED          0  /* undefined note */

/* all notes (frequencies) of the eighth octave */

const note_t NOTE_C8 		= 	4186010;
const note_t NOTE_Cis8 		= 	4434920;
const note_t NOTE_Des8	 	= 	NOTE_Cis8;
const note_t NOTE_D8 		= 	4698630;
const note_t NOTE_Dis8 		= 	4978030;
const note_t NOTE_Ees8  	=	NOTE_Dis8;
const note_t NOTE_E8		=	5274040;
const note_t NOTE_F8		=	5587650;
const note_t NOTE_Fis8  	=	5919910;
const note_t NOTE_Ges8  	=	NOTE_Fis8;
const note_t NOTE_G8		=	6271930;
const note_t NOTE_Gis8  	=	6644880;
const note_t NOTE_Aes8  	=	NOTE_Gis8;
const note_t NOTE_A8		=	7040000;
const note_t NOTE_Ais8  	=	7458620;
const note_t NOTE_B8  		=	NOTE_Ais8;
const note_t NOTE_H8		=	7902130;


/* helper macro to speed up declaration of all notes of one octave using the next higher octave */
#define DECLARE_NOTES(octave, higher_octave) \
		const note_t NOTE_C##octave = NOTE_C##higher_octave>>1; \
		const note_t NOTE_Cis##octave = NOTE_Cis##higher_octave>>1; \
		const note_t NOTE_Des##octave = NOTE_Des##higher_octave>>1; \
		const note_t NOTE_D##octave = NOTE_D##higher_octave>>1; \
		const note_t NOTE_Dis##octave = NOTE_Dis##higher_octave>>1; \
		const note_t NOTE_Ees##octave = NOTE_Ees##higher_octave>>1; \
		const note_t NOTE_E##octave = NOTE_E##higher_octave>>1; \
		const note_t NOTE_F##octave = NOTE_F##higher_octave>>1; \
		const note_t NOTE_Fis##octave = NOTE_Fis##higher_octave>>1; \
		const note_t NOTE_Ges##octave = NOTE_Ges##higher_octave>>1; \
		const note_t NOTE_G##octave = NOTE_G##higher_octave>>1; \
		const note_t NOTE_Gis##octave = NOTE_Gis##higher_octave>>1; \
		const note_t NOTE_Aes##octave = NOTE_Aes##higher_octave>>1; \
		const note_t NOTE_A##octave = NOTE_A##higher_octave>>1; \
		const note_t NOTE_Ais##octave = NOTE_Ais##higher_octave>>1; \
		const note_t NOTE_B##octave = NOTE_B##higher_octave>>1; \
		const note_t NOTE_H##octave = NOTE_H##higher_octave>>1;

DECLARE_NOTES(7,8)
DECLARE_NOTES(6,7)
DECLARE_NOTES(5,6)
DECLARE_NOTES(4,5)
DECLARE_NOTES(3,4)
DECLARE_NOTES(2,3)
DECLARE_NOTES(1,2)
DECLARE_NOTES(0,1)

#endif /* NOTE_H_ */
