/*
 * Buzzer.h
 *
 *  Created on: Mar 15, 2016
 *      Author: thebh_000
 */

#ifndef SOURCES_DRIVERS_BUZZER_BUZZER_H_
#define SOURCES_DRIVERS_BUZZER_BUZZER_H_

//enum for test.
typedef enum
{
   f_110Hz,
   f_220Hz,
   f_440Hz,
   f_880Hz,
   f_1760Hz,
   f_3520Hz,
   f_7040Hz,
   f_Off

} FREQ_OUT;

extern FREQ_OUT SelectedFreq;

extern void Buzzer_Tick();

//TODO: method that takes a frequency and outputs it to the buzzah.
//TODO: lookup table for a few octaves of notes within the range of the buzzer.

#endif /* SOURCES_DRIVERS_BUZZER_BUZZER_H_ */
