#include <Arduino.h>

#include "Ports.h"
#include "WiFi_ESP8266.h"

void setup () {

  Setup_Pins (PIN_COUNT, 13, 17, 20, 21, 22, 23, 24, 25);
  
  Serial.begin (115200);
  
  Setup_WiFi ();
}
 
void loop () {

  Process_WiFi ();
  
}
