#ifndef WIFI_ESP8266_H
#define WIFI_ESP8266_H

#include <Arduino.h>

#define DEBUG true

#define WIFI_SERIAL      Serial1
#define WIFI_SERIAL_BAUD 115200
#define WIFI_SSID        "clay-2.4ghz" // "Jackson 5" // "HOME-5EE4" // "joopal" // "AWS" // "shell-2.4GHz"
#define WIFI_PASS        "goldenbrown" // "tigertiger" // "316793944D3C0868" // "Cassandra2048" // "Codehappy123" // "technologydrive"
#define HTTP_SERVER_PORT "80"          // using port 8080 by default

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];

void Setup_ESP8266EX () {
  
  pinMode (3, OUTPUT); // Wi-Fi: ESP8266 breakout CH_PD (chip enable on ESP8266 IC)
  pinMode (4, OUTPUT); // Wi-Fi: ESP8266 breakout RST (reset on ESP8266 IC)
  pinMode (5, OUTPUT); // Wi-Fi: ESP8266 breakout GPIO0 (reset on ESP8266 IC)
  pinMode (8, OUTPUT); // Wi-Fi: ESP8266 breakout GPIO2 (reset on ESP8266 IC)

  digitalWrite (3, HIGH); // Set up CH_PD to enable the chip
  digitalWrite (4, HIGH); // Set up RST
  digitalWrite (5, HIGH); // Set up GPIO0. "At boot: low causes bootloader to enter flash upload mode; high causes normal boot" (from http://www.esp8266.com/wiki/doku.php?id=esp8266-module-family)
  digitalWrite (8, HIGH); // Set up GPIO2 in Working Mode

  delay (1000); // Let the device configuration stabilize

  WIFI_SERIAL.begin (WIFI_SERIAL_BAUD); // your esp's baud rate might be different
}

void Setup_WiFi () {
  
  Setup_ESP8266EX ();
}

String Send_Data (String command, const int timeout, boolean debug) {
  
  String response = "";
  
  WIFI_SERIAL.print (command); // Send the read character to the ESP8266EX
  
  long int time = millis ();
  
  while ((time + timeout) > millis ()) {
  
    while (WIFI_SERIAL.available ()) {
    
      // The ESP8266EX has data so display its output to the serial window 
      char c = WIFI_SERIAL.read (); // Read the next character.
      response += c;
    }  
  }
  
  if (debug) {
    Serial.print(response);
  }
  
  return response;
}

void Handle_Request (int connectionId, const char *requestType, const char *requestResource, const char *requestBody) {

  if (strncmp (requestResource, "/pins", 5) == 0) {

    if (strncmp (requestType, "POST", 4) == 0) {
      // TODO: cut out resource "/pins" (before ?)
      // TODO: make function to extract parameters in list "?id=1&value=high"
    } else if (strncmp (requestType, "GET", 3) == 0) {

      // Encode pin profile for sending
      String response = "";
      for (int i = 0; i < PIN_COUNT; i++) {
        response += String (Get_Pin_Mode (i)) + "," + String (Get_Pin_Value (i)) + "\n";
      }
      
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += response.length();
      cipSend += "\r\n";
      
      Send_Data (cipSend, 1000, DEBUG);
      Send_Data (response, 1000, DEBUG);
      
    }
    
  } else if (strncmp (requestResource, "/pin", 4) == 0) {

    if (strncmp (requestType, "POST", 4) == 0) {
      // TODO: cut out resource "/pins" (before ?)
      // TODO: make function to extract parameters in list "?id=1&value=high"

      Serial.println ("POST DATA:");
      Serial.println (requestBody);
      Serial.println ();

      char* parameters = strchr (requestResource, '?');
      if (parameters != NULL) { // i.e., if found the character '?'

        int parameterCount = 0;
        char* parameterKeys[10];
        char* parameterValues[10];

        // NOTE: Assuming proper formatting. This code needs to be make robust to erroneous and improperly-formatted parameter lists and parameter (key, value) pairs.
        // TODO: Make this code safe (see above note).

        char* nextParameter  = parameters; // Pointer to the next parameter to parse (including the preceding delimieter '?')
        char* parameterKey   = NULL;
        char* parameterValue = NULL;
        while (nextParameter != NULL) {

          // Locate the parameter's key and value the format "?key1=value1"
          parameterKey   = nextParameter + 1;
          parameterValue = strchr (parameterKey, '=') + 1;

          (parameterKey   - 1)[0] = '\0'; // Replace the '?' or '&' character with '\0' to terminate the key string.
          (parameterValue - 1)[0] = '\0'; // Replace the '=' character with '\0' to terminate the key string.

          parameterKeys[parameterCount]   = parameterKey;   // Store pointer to the parameter's key.
          parameterValues[parameterCount] = parameterValue; // Store pointer to the parameter's value.
          parameterCount++; // Increase the parameter count by one to account for this one.

          // Locate the next parameter.
          // NOTE: Here, if there's no parameter, nextParameter will be assigned NULL, causing the loop to terminate.
          nextParameter = strchr (parameterValue, '&'); // Search for the next parameter to determine the length of the parameter value substring.
          
          if (nextParameter != NULL) {
            nextParameter[0] = '\0'; // Replace the '&' character with '\0' to terminate the key string.
          }

          Serial.print ("parameterKey: "); Serial.println (parameterKey);
          Serial.print ("parameterValue: "); Serial.println (parameterValue);

          // TODO: Process request based on parameter values. Possibly cache the values.
        }
        
      }

      
    } else if (strncmp (requestType, "GET", 3) == 0) {
      if (strncmp (requestResource, "/pin/on", 7) == 0) {
        Set_Pin (0, OUTPUT, HIGH);
      } else if (strncmp (requestResource, "/pin/off", 8) == 0) {
        Set_Pin (0, OUTPUT, LOW); 
      }
    }

  } else if (strncmp (requestResource, "/pin/on", 7) == 0) {

    Set_Pin (0, OUTPUT, HIGH);

  } else if (strncmp (requestResource, "/pin/off", 8) == 0) {

    Set_Pin (0, OUTPUT, LOW);
    
  } else {
    
    String webpage = "<html><h1>Clay</h1></html>";
    
    String cipSend = "AT+CIPSEND=";
    cipSend += connectionId;
    cipSend += ",";
    cipSend += webpage.length();
    cipSend += "\r\n";
    
    Send_Data (cipSend, 1000, DEBUG);
    Send_Data (webpage, 1000, DEBUG);
    
//    webpage = "<button>LED2</button>";
//    
//    cipSend = "AT+CIPSEND=";
//    cipSend += connectionId;
//    cipSend += ",";
//    cipSend += webpage.length ();
//    cipSend += "\r\n";
//    
//    Send_Data (cipSend, 1000, DEBUG);
//    Send_Data (webpage, 1000, DEBUG);
  }
}

#endif
