#ifndef APPLICATION_H
#define APPLICATION_H

/* User includes (#include below this line is not maintained by Processor Expert) */

#include <stdio.h>
#include <stdlib.h>

#include "Utilities/Debug.h"
#include "Utilities/UUID.h"

//#include "Drivers/LEDs.h"
//#include "Drivers/PCA9552.h"
//#include "Drivers/MPU9250.h"

#include "Clock.h"

#include "ESP8266_Serial.h"
#include "Drivers/ESP8266.h"

#include "Bootloader.h"

#include "Behavior.h"
#include "Messenger.h"

void Application ();

#endif /* APPLICATION_H */
