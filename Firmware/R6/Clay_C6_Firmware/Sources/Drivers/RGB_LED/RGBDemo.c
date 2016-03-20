/*
 * RGBDemo.c
 *
 *  Created on: Feb 15, 2016
 *      Author: thebh
 */

////includes
#include "PE_Types.h"
#include "Clock.h"
#include "RGB_LED.h"
#include "LED1.h"
#include "Events.h"

////defines

////typedefs

////global vars

////local vars

////local function prototypes

////global function implementations

static int ledIndex = 0;
static int colorIndex = 0;
static RGB_Color currentColor = { 0, 0, 0 };

static uint8_t rTime = 30;
static uint8_t gTime = 31;
static uint8_t bTime = 32;

static uint8_t rMax = 0x60;
static uint8_t gMax = 0x57;
static uint8_t bMax = 0x5A;

static uint8_t rMin = 0x01;
static uint8_t gMin = 0x01;
static uint8_t bMin = 0x01;

static uint8_t rStep = 2;
static uint8_t gStep = 3;
static uint8_t bStep = 5;

static uint8_t r;
static uint8_t g;
static uint8_t b;

static bool rDescending = TRUE;
static bool gDescending = TRUE;
static bool bDescending = TRUE;

static bool LastState = FALSE;
static bool HbLedState = FALSE;
static bool BuzzerState = FALSE;

void RGBDemoLoop()
{
   r = rDescending ? rMax : rMin;
   g = gDescending ? gMax : gMin;
   b = bDescending ? bMax : bMin;

   for (int i = 0; i < RGB_MAX; ++i)
   {
      RGB_LED_SetState((RGB_LED) i, TRUE, LED_CURRENT_QUARTER);
   }

   for (;;)
   {
      if (!(Millis() % 15))
      {
         currentColor.R = r;
         currentColor.G = g;
         currentColor.B = b;

         for (int i = 0; i < RGB_MAX; ++i)
         {
            RGB_LED_SetColor((RGB_LED) i, &currentColor);
            RGB_LED_UpdateOutput();
         }
      }

      if (!(Millis() % rTime))
      {
         if (rDescending)
         {
            if (LastState != ButtonPressed || (r -= rStep) <= rMin)
            {
               rDescending = FALSE;
               if (!gDescending && !bDescending)
               {
                  LastState = ButtonPressed;
               }
            }
         }
         else
         {
            if ((r += rStep) >= rMax)
            {
               rDescending = TRUE;
            }
         }
      }

      if (!(Millis() % gTime))
      {
         if (gDescending)
         {
            if (LastState != ButtonPressed || (g -= gStep) <= gMin)
            {
               gDescending = FALSE;
               if (!rDescending && !bDescending)
               {
                  LastState = ButtonPressed;
               }
            }
         }
         else
         {
            if ((g += gStep) >= gMax)
            {
               gDescending = TRUE;
            }
         }
      }

      if (!(Millis() % bTime))
      {
         if (bDescending)
         {
            if (LastState != ButtonPressed || (b -= bStep) <= bMin)
            {
               bDescending = FALSE;
               if (!gDescending && !rDescending)
               {
                  LastState = ButtonPressed;
               }
            }
         }
         else
         {
            if ((b += bStep) >= bMax)
            {
               bDescending = TRUE;
            }
         }
      }

   }
}

////local function implementations
