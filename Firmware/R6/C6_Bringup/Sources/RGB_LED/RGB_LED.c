/*
 * RGB_LED.c
 *
 *  Created on: Jan 26, 2016
 *      Author: thebh
 */

////includes
#include "RGB_LED.h"
#include "PE_Types.h"
#include "I2C2.h"
#include "I2C.h"
#include "LED_SDB.h"
#include "Clock.h"

////defines
#define SHUTDOWN_REG_ADDR				0x00
#define REG_CTRL(x)                     (x + 0x25)      //control regs start at 1, run to 0x24
#define UPDATE_REGISTER					0x25
#define REG_PWM(x)                      (x)             //PWM regs start at 0x26, run to 0x49
#define GLOBAL_CONTROL_ADDR				0x4A
#define RESET_REG_ADDR   				0x4F

#define LED_CONTROL_OUT_MASK			0x01
#define LED_CONTROL_SL_MASK				0x06

#define RGB_LED_ADDR					0x3C

////typedefs
typedef struct
{
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
#if defined C6R2
static RGB_LED_Channel LED_Channels[RGB_MAX] =
{
   {  RGB1, 29, 30, 28},
   {  RGB2, 32, 33, 31},
   {  RGB3, 35, 36, 34},
   {  RGB4, 20, 21, 19},
   {  RGB5, 23, 24, 22},
   {  RGB6, 26, 27, 25},
   {  RGB7, 17, 18, 16},
   {  RGB8, 14, 15, 13},
   {  RGB9, 11, 12, 10},
   {  RGB10, 8, 9, 7},
   {  RGB11, 5, 6, 4},
   {  RGB12, 2, 3, 1}};
#else
static RGB_LED_Channel LED_Channels[RGB_MAX] = { { RGB1, 26, 27, 25 },
                                                 { RGB2, 23, 24, 22 },
                                                 { RGB3, 20, 21, 19 },
                                                 { RGB4, 35, 36, 34 },
                                                 { RGB5, 32, 33, 31 },
                                                 { RGB6, 29, 30, 28 },
                                                 { RGB7, 2, 3, 1 },
                                                 { RGB8, 5, 6, 4 },
                                                 { RGB9, 8, 9, 7 },
                                                 { RGB10, 11, 12, 10 },
                                                 { RGB11, 14, 15, 13 },
                                                 { RGB12, 17, 18, 16 } };
#endif
////local function prototypes

////global function implementations

bool RGB_LED_Enable()
{
   LED_SDB_PutVal(NULL, 1);

//reset all LEDs to off.

   uint8_t temp[] = { RESET_REG_ADDR, 0x00, SHUTDOWN_REG_ADDR, 0x01, GLOBAL_CONTROL_ADDR, 0x00 };     //shutdown register needs to be 1 to operate.

   I2C_Send_Message(temp, 2, RGB_LED_ADDR);
   Wait(1);
   I2C_Send_Message(temp + 2, 2, RGB_LED_ADDR);
   Wait(1);
   I2C_Send_Message(temp + 4, 2, RGB_LED_ADDR);

   for (int i = 0; i < RGB_MAX; ++i)
   {
      RGB_LED_SetState((RGB_LED) i, TRUE, LED_CURRENT_QUARTER);
   }
}

bool RGB_LED_Start()
{
}

bool RGB_LED_Stop()
{
}

bool RGB_LED_Pause()
{
}

void RGB_LED_SetState(RGB_LED LED, bool On, LED_Mode CurrentMax)
{
   uint8_t state = (On ? (1 & LED_CONTROL_OUT_MASK) | (CurrentMax & LED_CONTROL_SL_MASK) : 0);
   RGB_LED_Channel * l = LED_Channels + LED;

//keep track of last SL states locally? readback?

   uint8_t temp[] = { REG_CTRL(l->B_Index), state, state, state, UPDATE_REGISTER, 0x00 };     //start at blue, they are the lowest index on all LEDs

   I2C_Send_Message(temp + 4, 2, RGB_LED_ADDR);
   I2C_Send_Message(temp, 4, RGB_LED_ADDR);
   I2C_Send_Message(temp + 4, 2, RGB_LED_ADDR);

}

void RGB_LED_SetColor(RGB_LED LED, RGB_Color* Color)
{
   RGB_LED_Channel * l = LED_Channels + LED;

//keep track of last SL states locally? readback is not supported.

   uint8_t temp[] = { REG_PWM(l->B_Index), Color->B, Color->R, Color->G, UPDATE_REGISTER, 0x00 };     //start at blue, lowest index on all LEDs. green is highest

   I2C_Send_Message(temp + 4, 2, RGB_LED_ADDR);
   I2C_Send_Message(temp, 4, RGB_LED_ADDR);
   I2C_Send_Message(temp + 4, 2, RGB_LED_ADDR);

}

void RGB_LED_UpdateOutput()
{
   uint8_t temp[] = { UPDATE_REGISTER, 0x00 };
   I2C_Send_Message(temp, 2, RGB_LED_ADDR);
}
