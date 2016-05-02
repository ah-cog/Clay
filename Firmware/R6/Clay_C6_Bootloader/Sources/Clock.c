/*
 * Clock.c
 *
 *  Created on: Sep 10, 2015
 *      Author: thebh_000
 */

#include "Timer_1ms.h"
#include "LED1.h"
#include "LED2.h"
#include "Clock.h"
#include "Button.h"
#include "WiFi.h"

// defines ///////////////////

// structs ///////////////////

// global vars ///////////////
uint32_t power_on_time_msec;
uint8_t tick_1msec;
uint8_t tick_250msec;
uint8_t tick_500msec;
uint8_t tick_3000msec;

static bool led_state;

// function prototypes ///////

uint8_t Enable_Clock() {
   // Initialize the timer component
   (void) Timer_1ms_Init(NULL);
   LED1_Init(NULL);
   LED2_Init(NULL);

   //set this so that the counter will keep running when the debugger is attached.
   FTM0_CONF |= FTM_CONF_BDMMODE(3);

   return TRUE;
}

//reset all of the flags to false and the power on time to 0.
uint8_t Start_Clock() {

   power_on_time_msec = 0;
   tick_1msec = FALSE;
   tick_250msec = FALSE;
   tick_500msec = FALSE;
   tick_3000msec = FALSE;

   return TRUE;
}

//call this every 1msec to increment the power on time and set the flags.
void Tick() {

   ++power_on_time_msec;
   tick_1msec = TRUE;

   if (!(power_on_time_msec % 250)) {
      tick_250msec = TRUE;
   }

   if (!(power_on_time_msec % 500)) {
      tick_500msec = TRUE;
   }

   if (!(power_on_time_msec % 3000)) {
      tick_3000msec = TRUE;
   }
}

///will block for n milliseconds
void Wait(uint32_t milliseconds) {

   int start = power_on_time_msec;
   while (power_on_time_msec - start < milliseconds) {
      ;
   }
}

uint32_t Millis() {
   return power_on_time_msec;
}

void Monitor_Periodic_Events() {

   // LEDs
   if (tick_1msec) {
      tick_1msec = FALSE;

      Wifi_State_Step();
      Button_Periodic_Call();
   }

   if (tick_250msec) {
      tick_250msec = FALSE;

      //toggle LEDs
      LED1_PutVal(NULL, !led_state);
      LED2_PutVal(NULL, led_state);
      led_state = !led_state;
   }

   if (tick_500msec) {
      tick_500msec = FALSE;
   }

   if (tick_3000msec) {
      tick_3000msec = FALSE;
   }
}
