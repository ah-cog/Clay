#ifndef BUZZER_H
#define BUZZER_H

#include "PE_Types.h"

typedef enum {
	NOTE_C,
	NOTE_Db,
	NOTE_D,
	NOTE_Eb,
	NOTE_E,
	NOTE_F,
	NOTE_Gb,
	NOTE_G,
	NOTE_Ab,
	NOTE_A,
	NOTE_Bb,
	NOTE_B,
	NOTE_OFF,
	NOTE_INDEX_MAX
} NOTE_INDEX;

extern bool Buzzer_Enable ();

extern bool Buzzer_Disable ();

extern void Buzzer_Play_Note (NOTE_INDEX note, uint32_t duration);

extern void Buzzer_Play_Frequency (uint32_t frequency, uint32_t duration);

extern void Buzzer_Stop_Check ();

#endif
