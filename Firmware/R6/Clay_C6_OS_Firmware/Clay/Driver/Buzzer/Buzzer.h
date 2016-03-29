/*
 * Buzzer.h
 *
 *  Created on: Mar 15, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_DRIVERS_BUZZER_BUZZER_H_
#define SOURCES_DRIVERS_BUZZER_BUZZER_H_

////Includes //////////////////////////////////////////////////////
#include "stdint.h"
#include "stdbool.h"

////Macros ////////////////////////////////////////////////////////

////Typedefs  /////////////////////////////////////////////////////
//enum for test.
typedef enum
{
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

////Globals   /////////////////////////////////////////////////////

////Prototypes/////////////////////////////////////////////////////
extern bool Buzzer_Enable();

extern bool Buzzer_Disable();

extern void Buzzer_Play_Note(NOTE_INDEX note, uint32_t duration);

extern void Buzzer_Play_Frequency(uint32_t frequency, uint32_t duration);

extern void Buzzer_Stop_Check();

#endif /* SOURCES_DRIVERS_BUZZER_BUZZER_H_ */
