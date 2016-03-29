/*
 * Clay_Core_Hardware.c
 *
 *  Created on: Jan 26
 2016
 *      Author: thebh
 */
#include <Message.h>
#include "Clay_Core_Hardware.h"
#include "Clock.h"
#include "LED1.h"
#include "LED2.h"
#include "Drivers/RGB_LED/RGB_LED.h"
#include "Events.h"
#include "WIFI_RESET.h"
#include "mpu_9250_driver.h"
#include "MeshTest.h"
//#include "ESP8266.h"
////defines

////typedefs

////global vars

////local vars
static bool LED1_State;
static bool LED2_State;
bool status;

static mpu_values v = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

////local function prototypes

////global function implementations
//extern void Clay_Core_Init()
//{
//	LED1_State = FALSE;
//	LED2_State = TRUE;
//	BuzzerOutState = TRUE;
//	Clock_Start();
////	RGB_LED_Enable();
//
////	mpu_9250_init();
//
////	WIFI_RESET_PutVal(NULL, 0);
////	for (int i = 0; i < 10000; ++i)
////		;
////	WIFI_RESET_PutVal(NULL, 1);
//
//    // Message queue.
//    if ((status = Initialize_Message_Queue(&incomingMessageQueue)) != TRUE)
//    {
//        // Failure
//    }
//
//    if ((status = Initialize_Message_Queue(&outgoingMessageQueue)) != TRUE)
//    {
//        // Failure
//    }
//
//    // ESP8266, WiFi, HTTP, UDP.
//
//    if ((status = Enable_ESP8266()) != TRUE)
//    {
//        // Failure
//    }
//    // TODO: Generate SSID for AP according to regular expression and set up access point to facilitate discovery.
//
////#if !defined DONT_DO_WIFI_STUFF
//    if ((status = Enable_WiFi(SSID_DEFAULT, PASSWORD_DEFAULT)) != TRUE)
//    {
//        // Failure
//    }
//
//    if ((status = Start_HTTP_Server(HTTP_SERVER_PORT)) != TRUE)
//    {
//        // Failure
//    }
//
//    if ((Start_UDP_Server(MESSAGE_PORT)) != TRUE)
//    {
//        // Failure
//    }
//
//    if ((Start_Discovery_Broadcast()) != TRUE)
//    {
//        // Failure
//    }
//
////	MeshTestLoop();
//}

void Clay_Core_Update()
{

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
