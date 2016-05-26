#ifndef APPLICATION_H
#define APPLICATION_H

/* User includes (#include below this line is not maintained by Processor Expert) */

#include "Message.h"

#include <stdio.h>
#include <stdlib.h>

#include "Utilities/UUID.h"

//#include "Drivers/LEDs.h"
//#include "Drivers/PCA9552.h"
//#include "Drivers/MPU9250.h"
#include "Drivers/WiFi/WiFi.h"

#include "Clock.h"

#include "Action.h"
#include "Event.h"
#include "Timeline.h"

#include "Services/Interactive_Assembly.h"

// TODO: Move these into Device_Status.h
extern int8_t has_connection_to_wifi;
extern int8_t has_received_internet_address;
extern int8_t has_generated_discovery_broadcast_address;
extern int8_t has_enabled_broadcast;
extern char broadcast_address[32];
extern char local_address[32];

extern Observable_Interface *observable_interface;

extern void Enable_Observable_Interface ();

/**
 * Initializes the device.
 */
void Initialize ();

/**
 * Runs the application. This should be called only after calling Initialize().
 */
void Application ();


//HACK: the location, more than anything, I think is the hack. threw this in here for bay area maker faire. BAMF
extern void Blink_Leds();

#endif
