#ifndef APPLICATION_H
#define APPLICATION_H

/* User includes (#include below this line is not maintained by Processor Expert) */

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#include "Message.h"
//#include "LEDs.h"
//#include "PCA9552.h"
//#include "MPU9250.h"
#include "WiFi.h"
#include "Clock.h"
#include "UUID.h"
#include "Action.h"
#include "Event.h"
#include "Timeline.h"

/**
 * Initializes the device.
 */
void Initialize();

/**
 * Runs the application. This should be called only after calling Initialize().
 */
void Application();

#endif
