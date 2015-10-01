#include "Application.h"

// Clay's print, debug, and error messages.
//#define ENABLE_DEBUG_OUTPUT TRUE
//#if ENABLE_DEBUG_OUTPUT == TRUE
//	#define print(fmt, ...) printf("print: " fmt, __VA_ARGS__);
//	#define status(fmt, ...) printf("status: " fmt);
//	#define debug(fmt, ...) printf("%s:%d: " fmt, __FILE__, __LINE__, __VA_ARGS__);
//	#define error(fmt, ...) printf("%s:%d: " fmt, __FILE__, __LINE__, __VA_ARGS__);
//#else
//	#define print(fmt, ...) ; // (void) 0;
//	#define status(fmt, ...) ;
//	#define debug(fmt, ...) ; // (void) 0;
//	#define error(fmt, ...) ; // (void) 0;
//#endif

void Application (void) {
	
	char *dynamicString = NULL;
	
	/* Start Clay */
	
	printf ("Clay\r\n");
	
	printf ("\r\n");
	
	printf ("Enabling clock. ");
	Enable_Clock ();
	printf ("Done.\r\n");
	
	printf ("Starting clock. ");
	Start_Clock ();
	printf ("Done.\r\n");
	
	printf ("\r\n");
	
	printf ("Starting LEDs. ");
	Enable_PCA9552();
	Wait (5);
	Start_Light_Behavior (); // previously Start_Light_Feedback ()
	printf ("Done.\r\n");
	
	printf ("\r\n");
	
	printf ("Enabling ESP8266. ");
	Enable_ESP8266 ();
	printf ("Done.\r\n");
	
	// TODO: Enable_GPIO ()
	
	// TODO: Enable_MPU9250 ()
	// TODO: Start_Spatial_Sensing ()
	
	// Test dynamic memory allocation.
	/*
	dynamicString = (char *) malloc (16);
	strcpy (dynamicString, "tutorialspoint");
	printf("String = %s,  Address = %u\n", dynamicString, dynamicString);
	free(dynamicString);
	dynamicString = NULL;
	*/
	
	printf ("Enabling MPU-9250. ");
	mpu_9250_init();
	printf ("Done.\r\n");
	
	printf ("\r\n");
	
	Start_HTTP_Server (HTTP_SERVER_PORT);
	
	for (;;) {
		
		// Check and process any incoming requests
		Monitor_HTTP_Server ();
		
		// TODO: Monitor_Messages ();
		
		// TODO: Monitor_Orientation ();
		
		// TODO: Monitor_Behavior (); // TODO: In this function, Consider_Behavior (), Engage_Behavior (), Perform_Behavior ().
		
		// Check and perform "scheduled" periodic events
		Monitor_Periodic_Events ();
	}
}
