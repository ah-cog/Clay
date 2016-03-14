#ifndef APPLICATION_H
#define APPLICATION_H

/* User includes (#include below this line is not maintained by Processor Expert) */

#include <stdio.h>
#include <stdlib.h>

#include "Utilities/UUID.h"

//#include "Drivers/LEDs.h"
//#include "Drivers/PCA9552.h"
//#include "Drivers/MPU9250.h"
#include "Drivers/WiFi/WiFi.h"

#include "Clock.h"

//#include "ESP8266_Serial.h"
//#include "ESP8266.h"

#include "Behavior.h"
#include "Messenger.h"

/**
 * Initializes the device.
 */
void Initialize ();

/**
 * Runs the application. This should be called only after calling Initialize().
 */
void Application ();

#endif /* APPLICATION_H */
