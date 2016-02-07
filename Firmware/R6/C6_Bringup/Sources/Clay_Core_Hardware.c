/*
 * Clay_Core_Hardware.c
 *
 *  Created on: Jan 26
 2016
 *      Author: thebh
 */
#include "Clay_Core_Hardware.h"
#include "Clock.h"
#include "LED1.h"
#include "LED2.h"
#include "RGB_LED.h"
#include "BuzzerOut.h"
#include "Events.h"
#include "WIFI_RESET.h"
#include "mpu_9250_driver.h"
#include "MeshTest.h"
#include "Messenger.h"
#include "ESP8266.h"
////defines

////typedefs

////global vars

////local vars
static bool LED1_State;
static bool LED2_State;
static bool BuzzerOutState;
bool status;
static uint32_t TickCount; //todo: expose this?

static mpu_values v =
{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };

////local function prototypes

////global function implementations
extern void Clay_Core_Init()
{
	LED1_State = FALSE;
	LED2_State = TRUE;
	BuzzerOutState = TRUE;
	Clock_Start();
//	RGB_LED_Enable();

//	mpu_9250_init();

//	WIFI_RESET_PutVal(NULL, 0);
//	for (int i = 0; i < 10000; ++i)
//		;
//	WIFI_RESET_PutVal(NULL, 1);

    // Message queue.
    if ((status = Initialize_Message_Queue(&incomingMessageQueue)) != TRUE)
    {
        // Failure
    }

    if ((status = Initialize_Message_Queue(&outgoingMessageQueue)) != TRUE)
    {
        // Failure
    }

    // ESP8266, WiFi, HTTP, UDP.

    if ((status = Enable_ESP8266()) != TRUE)
    {
        // Failure
    }
    // TODO: Generate SSID for AP according to regular expression and set up access point to facilitate discovery.

//#if !defined DONT_DO_WIFI_STUFF
    if ((status = Enable_WiFi(SSID_DEFAULT, PASSWORD_DEFAULT)) != TRUE)
    {
        // Failure
    }

    if ((status = Start_HTTP_Server(HTTP_SERVER_PORT)) != TRUE)
    {
        // Failure
    }

    if ((Start_UDP_Server(MESSAGE_PORT)) != TRUE)
    {
        // Failure
    }

    if ((Start_Discovery_Broadcast()) != TRUE)
    {
        // Failure
    }

//	MeshTestLoop();
}

void Clay_Core_Update()
{
	if (tick_50us)
	{
		tick_50us = FALSE;

		switch (SelectedFreq)
		{
		case f_110Hz:
		{
			if (TickCount >= 182)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_220Hz:
		{
			if (TickCount >= 91)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_440Hz:
		{
			if (TickCount >= 45)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_880Hz:
		{
			if (TickCount >= 22)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_1760Hz:
		{
			if (TickCount >= 11)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_3520Hz:
		{
			if (TickCount >= 6)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_7040Hz:
		{
			if (TickCount >= 3)
			{
				BuzzerOutState = !BuzzerOutState;
				TickCount = 0;
			}
			break;
		}
		case f_Off:
		default:
		{
			break;
		}
		}

		++TickCount;
		BuzzerOut_PutVal(NULL, BuzzerOutState);
	}

	if (tick_1ms)
	{
		tick_1ms = FALSE;
	}
	if (tick_50ms)
	{
		tick_50ms = FALSE;
	}
	if (tick_250ms)
	{
		tick_250ms = FALSE;
		get_mpu_readings(&v);

		LED1_PutVal(NULL, LED1_State);
		LED2_PutVal(NULL, LED2_State);
		LED1_State = !LED1_State;
		LED2_State = !LED2_State;
	}

}

////local function implementations
