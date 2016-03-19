/*
 * Buzzer.c
 *
 *  Created on: Mar 15, 2016
 *      Author: thebh_000
 */

#include "Clock.h"
#include "Buzzer.h"

FREQ_OUT SelectedFreq;
static bool BuzzerOutState;
static uint32_t TickCount = 0;     //todo: expose this?

void Buzzer_Tick()
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
      BuzzerSwitch_PutVal(NULL, BuzzerOutState);
   }
}
