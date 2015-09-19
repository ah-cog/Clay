/*
 * GPIO.c
 *
 *  Created on: Sep 17, 2015
 *      Author: mokogobo
 */

#include "GPIO.h"

uint8_t Enable_Channels () {
	(void) IO_1_Init (NULL);
	(void) IO_2_Init (NULL);
	(void) IO_3_Init (NULL);
	(void) IO_4_Init (NULL);
	(void) IO_5_Init (NULL);
	(void) IO_6_Init (NULL);
	(void) IO_7_Init (NULL);
	(void) IO_8_Init (NULL);
	(void) IO_9_Init (NULL);
	(void) IO_10_Init (NULL);
	(void) IO_11_Init (NULL);
	(void) IO_12_Init (NULL);
	
	return TRUE;
}

void Set_Channel (uint8_t number, uint8_t direction, uint8_t mode) {
	
	uint8_t directionValue = 0;
	
	// Prepare to set direction as input or output.
	if (direction == INPUT_CHANNEL) {
		directionValue = TRUE; // Set as output.
	} else if (direction == OUTPUT_CHANNEL) {
		directionValue = FALSE; // Set as input.
	}
	
	// Actually set the channel based on preparations above.
	if (number == 1) {
		IO_1_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 2) {
		IO_2_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 3) {
		IO_3_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 4) {
		IO_4_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 5) {
		IO_5_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 6) {
		IO_6_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 7) {
		IO_7_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 8) {
		IO_8_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 9) {
		IO_9_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 10) {
		IO_10_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 11) {
		IO_11_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	} else if (number == 12) {
		IO_12_SetDir (NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
}

void Set_Channel_State (uint8_t number, uint8_t state) { // i.e., set discrete state of the channel (on or off)
	
	uint8_t stateValue = 0;
	
	// TODO: Set the specified channel to be an output if it is not configured as such (and save state if it was an input so it can resume that behavior later).
	
	// Prepare to set direction as input or output.
	if (state == ON_CHANNEL) {
		stateValue = TRUE; // Set as output.
	} else if (state == OFF_CHANNEL) {
		stateValue = FALSE; // Set as input.
	}
	
	// Actually set the channel based on preparations above.
	if (number == 1) {
		IO_1_PutVal (NULL, stateValue);
	} else if (number == 2) {
		IO_2_PutVal (NULL, stateValue);
	} else if (number == 3) {
		IO_3_PutVal (NULL, stateValue);
	} else if (number == 4) {
		IO_4_PutVal (NULL, stateValue);
	} else if (number == 5) {
		IO_5_PutVal (NULL, stateValue);
	} else if (number == 6) {
		IO_6_PutVal (NULL, stateValue);
	} else if (number == 7) {
		IO_7_PutVal (NULL, stateValue);
	} else if (number == 8) {
		IO_8_PutVal (NULL, stateValue);
	} else if (number == 9) {
		IO_9_PutVal (NULL, stateValue);
	} else if (number == 10) {
		IO_10_PutVal (NULL, stateValue);
	} else if (number == 11) {
		IO_11_PutVal (NULL, stateValue);
	} else if (number == 12) {
		IO_12_PutVal (NULL, stateValue);
	}
}

uint8_t Get_Channel_State (uint8_t number) { // i.e., get discrete input state
	
	// Actually set the channel based on preparations above.
	if (number == 1) {
		return (uint8_t) IO_1_GetVal (NULL);
	} else if (number == 2) {
		return (uint8_t) IO_2_GetVal (NULL);
	} else if (number == 3) {
		return (uint8_t) IO_3_GetVal (NULL);
	} else if (number == 4) {
		return (uint8_t) IO_4_GetVal (NULL);
	} else if (number == 5) {
		return (uint8_t) IO_5_GetVal (NULL);
	} else if (number == 6) {
		return (uint8_t) IO_6_GetVal (NULL);
	} else if (number == 7) {
		return (uint8_t) IO_7_GetVal (NULL);
	} else if (number == 8) {
		return (uint8_t) IO_8_GetVal (NULL);
	} else if (number == 9) {
		return (uint8_t) IO_9_GetVal (NULL);
	} else if (number == 10) {
		return (uint8_t) IO_10_GetVal (NULL);
	} else if (number == 11) {
		return (uint8_t) IO_11_GetVal (NULL);
	} else if (number == 12) {
		return (uint8_t) IO_12_GetVal (NULL);
	}
}
