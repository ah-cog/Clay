/*
 * Clay_Core_Hardware.h
 *
 *  Created on: Jan 26, 2016
 *      Author: thebh
 */

#ifndef SOURCES_CLAY_CORE_HARDWARE_H_
#define SOURCES_CLAY_CORE_HARDWARE_H_

typedef enum
{
	f_110Hz, f_220Hz, f_440Hz, f_880Hz, f_1760Hz, f_3520Hz, f_7040Hz, f_Off

} FREQ_OUT;

extern void Clay_Core_Init();
extern void Clay_Core_Update();

#endif /* SOURCES_CLAY_CORE_HARDWARE_H_ */
