#include "RGB_LED.h"
#include "PE_Types.h"
#include "I2C0.h"
#include "Drivers/I2C/I2C.h"
#include "LED_SDB.h"
#include "Clock.h"

#define SHUTDOWN_REG_ADDR				0x00
#define REG_CTRL(x)                     (x + 0x25)      //control regs start at 1, run to 0x24
#define UPDATE_REGISTER					0x25
#define REG_PWM(x)                      (x)             //PWM regs start at 0x26, run to 0x49
#define GLOBAL_CONTROL_ADDR				0x4A
#define RESET_REG_ADDR   				0x4F

#define LED_CONTROL_OUT_MASK			0x01
#define LED_CONTROL_SL_MASK				0x06

#define RGB_LED_ADDR					0x3C

Channel_Light proposed_light_profiles[CHANNEL_COUNT];
Channel_Light channelLightProfiles[CHANNEL_COUNT];

typedef struct {
	RGB_LED RGB_Index;     //the LED's clay-specific port index
	uint8_t R_Index;     //the LED driver output driving the red for this LED
	uint8_t G_Index;     //the LED driver output driving the green for this LED
	uint8_t B_Index;
//the LED driver output driving the blue for this LED
} RGB_LED_Channel;

////global vars

//LED	C6R1	C6R2	R	G	B
//DS4	7	    12	    2	3	1
//DS5	8	    11	    5	6	4
//DS6	9	    10	    8	9	7
//DS7	10	    9	    11	12	10
//DS8	11	    8	    14	15	13
//DS9	12	    7	    17	18	16
//DS10	3	    4	    20	21	19
//DS11	2	    5	    23	24	22
//DS12	1	    6	    26	27	25
//DS13	4	    3	    35	36	34
//DS14	5	    2	    32	33	31
//DS15	6	    1	    29	30	28

//PwmReg = CHANNEL_INDEX
//CtrlReg= CHANNEL_INDEX + 0x25

////local vars
//static RGB_LED_Channel LED_Channels[RGB_MAX] = { { RGB1, 11, 12, 10 }, { RGB2, 14, 15, 13 }, { RGB3, 17, 18, 16 }, { RGB5, 23, 24, 22 }, { RGB4, 26, 27, 25 }, { RGB6, 20, 21, 19 }, { RGB7, 35, 36, 34 }, { RGB8, 32, 33, 31 }, { RGB9, 29, 30, 28 }, {
//		RGB10, 8, 9, 7 }, { RGB11, 5, 6, 4 }, { RGB12, 2, 3, 1 } };
static RGB_LED_Channel LED_Channels[RGB_MAX] = {
		{ RGB1, 11, 12, 10 },
		{ RGB2, 14, 15, 13 },
		{ RGB3, 17, 18, 16 },
		{ RGB4, 26, 27, 25 },
		{ RGB5, 23, 24, 22 },
		{ RGB6, 20, 21, 19 },
		{ RGB7, 35, 36, 34 },
		{ RGB8, 32, 33, 31 },
		{ RGB9, 29, 30, 28 },
		{ RGB12, 2, 3, 1 },
		{ RGB11, 5, 6, 4 },
		{ RGB10, 8, 9, 7 }
};
////local function prototypes

////global function implementations

bool RGB_LED_Enable () {
	LED_SDB_PutVal (NULL, 1);

//reset all LEDs to off.

	uint8_t temp[] = { RESET_REG_ADDR, 0x00, SHUTDOWN_REG_ADDR, 0x01,
	GLOBAL_CONTROL_ADDR, 0x00 }; //shutdown register needs to be 1 to operate.

	I2C_Send_Message (temp, 2, RGB_LED_ADDR);
	Wait (1);
	I2C_Send_Message (temp + 2, 2, RGB_LED_ADDR);
	Wait (1);
	I2C_Send_Message (temp + 4, 2, RGB_LED_ADDR);

	for (int i = 0; i < RGB_MAX; ++i) {
		RGB_LED_SetState ((RGB_LED) i, TRUE, LED_CURRENT_QUARTER);
	}
}

bool RGB_LED_Start () {
}

bool RGB_LED_Stop () {
}

bool RGB_LED_Pause () {
}

void RGB_LED_SetState (RGB_LED LED, bool On, LED_Mode CurrentMax) {
	uint8_t state = (On ? (1 & LED_CONTROL_OUT_MASK) | (CurrentMax & LED_CONTROL_SL_MASK) : 0);
	RGB_LED_Channel * l = LED_Channels + LED;

//keep track of last SL states locally? readback?

	uint8_t temp[] = { REG_CTRL(l->B_Index), state, state, state,
	UPDATE_REGISTER, 0x00 }; //start at blue, they are the lowest index on all LEDs

	I2C_Send_Message (temp + 4, 2, RGB_LED_ADDR);
	I2C_Send_Message (temp, 4, RGB_LED_ADDR);
	I2C_Send_Message (temp + 4, 2, RGB_LED_ADDR);

}

void RGB_LED_SetColor (RGB_LED LED, RGB_Color* Color) {
	RGB_LED_Channel * l = LED_Channels + LED;

//keep track of last SL states locally? readback is not supported.

	uint8_t temp[] = { REG_PWM(l->B_Index), Color->B, Color->R, Color->G,
	UPDATE_REGISTER, 0x00 }; //start at blue, lowest index on all LEDs. green is highest

	I2C_Send_Message (temp + 4, 2, RGB_LED_ADDR);
	I2C_Send_Message (temp, 4, RGB_LED_ADDR);
	I2C_Send_Message (temp + 4, 2, RGB_LED_ADDR);

}

void RGB_LED_UpdateOutput () {
	uint8_t temp[] = { UPDATE_REGISTER, 0x00 };
	I2C_Send_Message (temp, 2, RGB_LED_ADDR);
}

int8_t Start_Light_Behavior () {
	//stubbed.
}

int8_t Initialize_Color_Palette () {

	// Mix the "on" color
	onColor.R = 0;
	onColor.G = 100;
	onColor.B = 200;

	// Mix the "off" color
	offColor.R = 0;
	offColor.G = 0;
	offColor.B = 0;
}

void Set_Light_Color (Channel_Light *channel_light, uint8_t red, uint8_t green, uint8_t blue) {
	(*channel_light).color.R = red;
	(*channel_light).color.G = green;
	(*channel_light).color.B = blue;
}

int8_t Initialize_Channel_Lights () {
	int i;

	for (i = 0; i < CHANNEL_COUNT; i++) {

		// Initialize update channel profile
		proposed_light_profiles[i].number = (i + 1);
		proposed_light_profiles[i].enabled = TRUE;
		Set_Light_Color (&proposed_light_profiles[i], 0, 0, 0);

		// Initialize channel profile
		channelLightProfiles[i].number = (i + 1);
		channelLightProfiles[i].enabled = TRUE;
		Set_Light_Color (&channelLightProfiles[i], 0, 0, 0);
	}

	return TRUE;
}

void Reset_Channel_Lights () {
	int i;

	for (i = 0; i < CHANNEL_COUNT; i++) {

		// Initialize update channel profile
		proposed_light_profiles[i].number = (i + 1);
		proposed_light_profiles[i].enabled = TRUE;
		Set_Light_Color (&proposed_light_profiles[i], 0, 0, 0);
	}

//	return TRUE;
}

int8_t Apply_Channel_Lights () {
	int i;

	for (i = 0; i < CHANNEL_COUNT; i++) {

		// Check if the enable state changed. Apply the corresponding transform.
		if (proposed_light_profiles[i].enabled != channel_profile[i].enabled) {

			// Update state.
			channelLightProfiles[i].enabled = proposed_light_profiles[i].enabled;

			if (channelLightProfiles[i].enabled == TRUE) {

				// Apply state.
				Enable_Channel (channelLightProfiles[i].number, channelLightProfiles[i].enabled);

				// Check if the direction change. Apply the corresponding transform if it changed.
//				if ((proposed_light_profiles[i].color.R != channelLightProfiles[i].color.R)
//						|| (proposed_light_profiles[i].color.G != channelLightProfiles[i].color.G)
//						|| (proposed_light_profiles[i].color.B != channelLightProfiles[i].color.B))
//				{

				// Update color.
				channelLightProfiles[i].color.R = proposed_light_profiles[i].color.R;
				channelLightProfiles[i].color.G = proposed_light_profiles[i].color.G;
				channelLightProfiles[i].color.B = proposed_light_profiles[i].color.B;

				// Apply color.
				RGB_LED_SetColor ((RGB_LED) (channelLightProfiles[i].number - 1), &(channelLightProfiles[i].color));
//				}

			} else if (channelLightProfiles[i].enabled == FALSE) {

				// Apply color.
				RGB_LED_SetColor ((RGB_LED) (channelLightProfiles[i].number - 1), &offColor);

			}
		}
	}

	return TRUE;
}

bool Perform_Channel_Light_Effect (bool reverse) {
	RGB_Color c = { 0, 0, 0 };

	for (c.R = 0; c.R <= 200; c.R += 70) {
		for (c.G = 0; c.G <= 200; c.G += 70) {
			for (c.B = 0; c.B <= 200; c.B += 70) {
				for (int i = reverse ? RGB_MAX : 0; reverse ? i >= 0 : i < RGB_MAX; i += (reverse ? -1 : 1)) {
					RGB_LED_SetColor ((RGB_LED) i, &c);
					Wait (1);
				}
			}
		}
	}

	c.R = 0;
	c.G = 0;
	c.B = 0;

	for (int i = 0; i < RGB_MAX; ++i) {
		RGB_LED_SetColor ((RGB_LED) i, &c);
	}

	return TRUE;
}
