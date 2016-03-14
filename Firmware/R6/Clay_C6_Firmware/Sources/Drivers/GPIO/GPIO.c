#include "GPIO.h"

Channel updateChannelProfile[CHANNEL_COUNT];
Channel channelProfile[CHANNEL_COUNT];

Channel_Light updateChannelLightProfiles[CHANNEL_COUNT];
Channel_Light channelLightProfiles[CHANNEL_COUNT];

int8_t Initialize_Channels()
{
	int i;

	for (i = 0; i < CHANNEL_COUNT; i++)
	{

		// Initialize update channel profile
		updateChannelProfile[i].number = (i + 1);
		updateChannelProfile[i].enabled = FALSE;
		updateChannelProfile[i].direction = CHANNEL_DIRECTION_OUTPUT;
		updateChannelProfile[i].mode = CHANNEL_MODE_TOGGLE;
		updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;

		// Initialize channel profile
		channelProfile[i].number = (i + 1);
		channelProfile[i].enabled = FALSE;
		channelProfile[i].direction = CHANNEL_DIRECTION_OUTPUT;
		channelProfile[i].mode = CHANNEL_MODE_TOGGLE;
		channelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
	}

	return TRUE;
}

int8_t Reset_Channels()
{
	int i;

	for (i = 0; i < CHANNEL_COUNT; i++)
	{

		// Initialize update channel profile
		updateChannelProfile[i].number = (i + 1);
		updateChannelProfile[i].enabled = FALSE;
		updateChannelProfile[i].direction = CHANNEL_DIRECTION_OUTPUT;
		updateChannelProfile[i].mode = CHANNEL_MODE_TOGGLE;
		updateChannelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;

//		// Initialize channel profile
//		channelProfile[i].number = (i + 1);
//		channelProfile[i].enabled = FALSE;
//		channelProfile[i].direction = CHANNEL_DIRECTION_OUTPUT;
//		channelProfile[i].mode = CHANNEL_MODE_TOGGLE;
//		channelProfile[i].value = CHANNEL_VALUE_TOGGLE_OFF;
	}

	return TRUE;
}

//int8_t Update_Channels () {
//	int i;
//	
//	// Copy the updated state into the internal state
//	// Save the current state in the cloud history
//	// Set the internal state as updated so it won't be updated again
//	
//	for (i = 0; i < CHANNEL_COUNT; i++) {
//
//		// Check if the enable state changed. Apply the corresponding transform.
//		if (updateChannelProfile[i].enabled != channelProfile[i].enabled) {
//			channelProfile[i] = updateChannelProfile[i];
//		}
//		
//		// Check if the direction change. Apply the corresponding transform.
//		if (updateChannelProfile[i].direction != channelProfile[i].direction) {
//			channelProfile[i].direction = updateChannelProfile[i];
//		}
//		
//		// Check if the mode change. Apply the corresponding transform.
//		if (updateChannelProfile[i].mode != channelProfile[i].mode) {
//			channelProfile[i].mode = updateChannelProfile[i].mode;
//		}
//		
//		// Check if the value change. Apply the corresponding transform.
//		if (updateChannelProfile[i].value != channelProfile[i].value) {
//			channelProfile[i].value = updateChannelProfile[i].value;
//		}
//		
//	}
//	
//	return TRUE;
//}

// TODO: Apply only changes! Compare current state to previous state or to actual hardware state. The former might be faster, but it's less "ground truth."
int8_t Apply_Channels()
{
	int i;

	for (i = 0; i < CHANNEL_COUNT; i++)
	{

		// Check if the enable state changed. Apply the corresponding transform.
		if (updateChannelProfile[i].enabled != channelProfile[i].enabled)
		{

			// Update state.
			channelProfile[i].enabled = updateChannelProfile[i].enabled;

			if (channelProfile[i].enabled == TRUE)
			{

				// Apply state.
				Enable_Channel(channelProfile[i].number, channelProfile[i].enabled);

				// Check if the direction change. Apply the corresponding transform if it changed.
				if (updateChannelProfile[i].direction != channelProfile[i].direction)
				{

					// Update direction.
					channelProfile[i].direction = updateChannelProfile[i].direction;

					// Apply direction.
					Set_Channel(channelProfile[i].number, channelProfile[i].direction, channelProfile[i].mode);
				}

				// Check if the mode change. Apply the corresponding transform if it changed.
				if (updateChannelProfile[i].mode != channelProfile[i].mode)
				{

					// Update mode.
					channelProfile[i].mode = updateChannelProfile[i].mode;

					// Apply mode.
					Set_Channel(channelProfile[i].number, channelProfile[i].direction, channelProfile[i].mode);
				}

				// Check if the value change. Apply the corresponding transform if it changed.
				if (updateChannelProfile[i].value != channelProfile[i].value)
				{

					// Update value.
					channelProfile[i].value = updateChannelProfile[i].value;

					// Apply value.
					if (channelProfile[i].direction == CHANNEL_DIRECTION_INPUT)
					{
						//					channelProfile[i].value = IO_1_GetVal (NULL);
						//					channelProfile[i].value = (uint16_t) Get_Channel_Value (channelProfile[i].number);
					}
					else if (channelProfile[i].direction == CHANNEL_DIRECTION_OUTPUT)
					{
						Set_Channel_Value(channelProfile[i].number, channelProfile[i].value);
					}
				}

			}
			else if (channelProfile[i].enabled == FALSE)
			{

				// Apply direction and mode.
				Set_Channel(channelProfile[i].number, CHANNEL_DIRECTION_OUTPUT, CHANNEL_MODE_TOGGLE);

				// Apply value.
				Set_Channel_Value(channelProfile[i].number, CHANNEL_VALUE_TOGGLE_OFF);

			}
		}
	}

	return TRUE;
}

// TODO: Remove this? Just use the above one that does per-channel enabling?
int8_t Enable_Channels()
{
	(void) IO_1_Init(NULL);
	(void) IO_2_Init(NULL);
	(void) IO_3_Init(NULL);
	(void) IO_4_Init(NULL);
	(void) IO_5_Init(NULL);
	(void) IO_6_Init(NULL);
	(void) IO_7_Init(NULL);
	(void) IO_8_Init(NULL);
	(void) IO_9_Init(NULL);
	(void) IO_10_Init(NULL);
	(void) IO_11_Init(NULL);
	(void) IO_12_Init(NULL);

	return TRUE;
}

int8_t Enable_Channel(uint8_t number, uint8_t enabled)
{

	channelProfile[(number - 1)].enabled = enabled;

	// TODO: Allow disabling!
	if (number == 1)
	{
		(void) IO_1_Init(NULL);
	}
	else if (number == 2)
	{
		(void) IO_2_Init(NULL);
	}
	else if (number == 3)
	{
		(void) IO_3_Init(NULL);
	}
	else if (number == 4)
	{
		(void) IO_4_Init(NULL);
	}
	else if (number == 5)
	{
		(void) IO_5_Init(NULL);
	}
	else if (number == 6)
	{
		(void) IO_6_Init(NULL);
	}
	else if (number == 7)
	{
		(void) IO_7_Init(NULL);
	}
	else if (number == 8)
	{
		(void) IO_8_Init(NULL);
	}
	else if (number == 9)
	{
		(void) IO_9_Init(NULL);
	}
	else if (number == 10)
	{
		(void) IO_10_Init(NULL);
	}
	else if (number == 11)
	{
		(void) IO_11_Init(NULL);
	}
	else if (number == 12)
	{
		(void) IO_12_Init(NULL);
	}

	return TRUE;
}

void Set_Channel(uint8_t number, uint8_t direction, uint8_t mode)
{

	uint8_t directionValue = 0;

	// Prepare to set direction as input or output.
	if (direction == CHANNEL_DIRECTION_OUTPUT)
	{
		directionValue = TRUE; // Set as output.
	}
	else if (direction == CHANNEL_DIRECTION_INPUT)
	{
		directionValue = FALSE; // Set as input.
	}

	// Actually set the channel based on preparations above.
	if (number == 1)
	{
		IO_1_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 2)
	{
		IO_2_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 3)
	{
		IO_3_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 4)
	{
		IO_4_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 5)
	{
		IO_5_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 6)
	{
		IO_6_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 7)
	{
		IO_7_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 8)
	{
		IO_8_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 9)
	{
		IO_9_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 10)
	{
		IO_10_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 11)
	{
		IO_11_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
	else if (number == 12)
	{
		IO_12_SetDir(NULL, directionValue); // Set as output.
		// TODO: Set mode (i.e., digital or analog)
	}
}

void Set_Channel_Value(uint8_t number, uint8_t value)
{ // i.e., set discrete state of the channel (on or off)

	uint8_t stateValue = 0;

	// TODO: Set the specified channel to be an output if it is not configured as such (and save state if it was an input so it can resume that behavior later).

	// Prepare to set direction as input or output.
	if (value == CHANNEL_VALUE_TOGGLE_ON)
	{
		stateValue = TRUE; // Set as output.
	}
	else if (value == CHANNEL_VALUE_TOGGLE_OFF)
	{
		stateValue = FALSE; // Set as input.
	}

	// Actually set the channel based on preparations above.
	if (number == 1)
	{
		IO_1_PutVal(NULL, stateValue);
	}
	else if (number == 2)
	{
		IO_2_PutVal(NULL, stateValue);
	}
	else if (number == 3)
	{
		IO_3_PutVal(NULL, stateValue);
	}
	else if (number == 4)
	{
		IO_4_PutVal(NULL, stateValue);
	}
	else if (number == 5)
	{
		IO_5_PutVal(NULL, stateValue);
	}
	else if (number == 6)
	{
		IO_6_PutVal(NULL, stateValue);
	}
	else if (number == 7)
	{
		IO_7_PutVal(NULL, stateValue);
	}
	else if (number == 8)
	{
		IO_8_PutVal(NULL, stateValue);
	}
	else if (number == 9)
	{
		IO_9_PutVal(NULL, stateValue);
	}
	else if (number == 10)
	{
		IO_10_PutVal(NULL, stateValue);
	}
	else if (number == 11)
	{
		IO_11_PutVal(NULL, stateValue);
	}
	else if (number == 12)
	{
		IO_12_PutVal(NULL, stateValue);
	}
}

int8_t Get_Channel_Value(uint8_t number)
{ // i.e., Get discrete input state

	uint8_t value = NULL;

	// Actually set the channel based on preparations above.
	if (number == 1)
	{
		value = (uint8_t) IO_1_GetVal(NULL);
	}
	else if (number == 2)
	{
		value = (uint8_t) IO_2_GetVal(NULL);
	}
	else if (number == 3)
	{
		value = (uint8_t) IO_3_GetVal(NULL);
	}
	else if (number == 4)
	{
		value = (uint8_t) IO_4_GetVal(NULL);
	}
	else if (number == 5)
	{
		value = (uint8_t) IO_5_GetVal(NULL);
	}
	else if (number == 6)
	{
		value = (uint8_t) IO_6_GetVal(NULL);
	}
	else if (number == 7)
	{
		value = (uint8_t) IO_7_GetVal(NULL);
	}
	else if (number == 8)
	{
		value = (uint8_t) IO_8_GetVal(NULL);
	}
	else if (number == 9)
	{
		value = (uint8_t) IO_9_GetVal(NULL);
	}
	else if (number == 10)
	{
		value = (uint8_t) IO_10_GetVal(NULL);
	}
	else if (number == 11)
	{
		value = (uint8_t) IO_11_GetVal(NULL);
	}
	else if (number == 12)
	{
		value = (uint8_t) IO_12_GetVal(NULL);
	}

	return value;
}

int8_t Initialize_Channel_Lights()
{
	int i;

	for (i = 0; i < CHANNEL_COUNT; i++)
	{

		// Initialize update channel profile
		updateChannelLightProfiles[i].number = (i + 1);
		updateChannelLightProfiles[i].enabled = TRUE;
		updateChannelLightProfiles[i].color = &offColor;

		// Initialize channel profile
		channelLightProfiles[i].number = (i + 1);
		channelLightProfiles[i].enabled = TRUE;
		channelLightProfiles[i].color = &offColor;
	}

	return TRUE;
}

void Reset_Channel_Lights()
{
	int i;

	for (i = 0; i < CHANNEL_COUNT; i++)
	{

		// Initialize update channel profile
		updateChannelLightProfiles[i].number = (i + 1);
		updateChannelLightProfiles[i].enabled = TRUE;
		updateChannelLightProfiles[i].color = &offColor;
	}

//	return TRUE;
}

int8_t Apply_Channel_Lights()
{
	int i;

	for (i = 0; i < CHANNEL_COUNT; i++)
	{

		// Check if the enable state changed. Apply the corresponding transform.
		if (updateChannelLightProfiles[i].enabled != channelProfile[i].enabled)
		{

			// Update state.
			channelLightProfiles[i].enabled = updateChannelLightProfiles[i].enabled;

			if (channelLightProfiles[i].enabled == TRUE)
			{

				// Apply state.
				Enable_Channel(channelLightProfiles[i].number, channelLightProfiles[i].enabled);

				// Check if the direction change. Apply the corresponding transform if it changed.
				if (updateChannelLightProfiles[i].color != channelLightProfiles[i].color)
				{

					// Update color.
					channelLightProfiles[i].color = updateChannelLightProfiles[i].color;

					// Apply color.
					RGB_LED_SetColor((RGB_LED)(channelLightProfiles[i].number - 1), channelLightProfiles[i].color);
				}

			}
			else if (channelLightProfiles[i].enabled == FALSE)
			{

				// Apply color.
				RGB_LED_SetColor((RGB_LED)(channelLightProfiles[i].number - 1), &offColor);

			}
		}
	}

	return TRUE;
}
