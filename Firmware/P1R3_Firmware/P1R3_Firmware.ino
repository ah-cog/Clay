#include "Ports.h"
#include "WiFi_ESP8266.h"

// By default we are looking for OK\r\n
char OKrn[] = "OK\r\n";
byte Wait_For_Response (int timeout, char* term=OKrn) {
  
  unsigned long t = millis();
  bool found = false;
  int i = 0;
  int len = strlen (term);
  
  // wait for at most timeout milliseconds
  // or if OK\r\n is found
  while (millis () < (t + timeout)) {
    if (WIFI_SERIAL.available ()) {
      buffer[i++] = WIFI_SERIAL.read ();
      if(i >= len) {
        if (strncmp ((buffer + i - len), term, len) == 0) {
          found = true;
          break;
        }
      }
    }
  }
  
  buffer[i] = 0;
  Serial.print (buffer);
  return found;
}

void setup () {

  Setup_Pins (PIN_COUNT, 13, 17, 20, 21, 22, 23, 24, 25);
  
  Setup_WiFi ();
  
  Serial.begin (115200);
  
//  Send_Data ("AT+RST\r\n",2000,DEBUG); // reset module
//  Send_Data ("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
//  Send_Data ("AT+CIFSR\r\n",1000,DEBUG); // get ip address
//  Send_Data ("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
//  Send_Data ("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80

  Send_Data ("AT+CWSAP=\"Clay AP\",\"1234567890\",5,3\r\n", 5000, DEBUG); // Configure access point (AP) name, password, channel, and security mode (Reference: https://github.com/espressif/esp8266_at/wiki/CWSAP)
  Send_Data ("AT+RST\r\n", 2000, DEBUG); // reset module
  Send_Data ("AT+CWMODE=3\r\n", 1000, DEBUG); // configure as access point

  WIFI_SERIAL.print ("AT+CWJAP=\"");
  WIFI_SERIAL.print (WIFI_SSID);
  WIFI_SERIAL.print ("\",\"");
  WIFI_SERIAL.print (WIFI_PASS);
  WIFI_SERIAL.println ("\"");
  Wait_For_Response (10000);
  
  Send_Data ("AT+CIFSR\r\n", 1000, DEBUG); // get ip address
  Send_Data ("AT+CIPMUX=1\r\n", 1000, DEBUG); // configure for multiple connections
  
  // Send_Data ("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // turn on server on port 80
  WIFI_SERIAL.print ("AT+CIPSERVER=1,");
  WIFI_SERIAL.print (HTTP_SERVER_PORT);
  WIFI_SERIAL.print ("\r\n");
  Wait_For_Response (1000);
}
 
void loop () {
  
  if (WIFI_SERIAL.available ()) { // check if the esp is sending a message

    // For multiple connection mode (CIPMUX=1): +IPD,<id>,<length>:<data>
    // For single connection mode (CIPMUX=0): +IPD,<length>:<data>
    if (WIFI_SERIAL.find ("+IPD,")) { // Look for the beginning of a request

      // Read the request line
      String lineString = WIFI_SERIAL.readStringUntil ('\n');

      Serial.print ("LINE: "); Serial.println (lineString);
      Serial.println ();
      Serial.println ();
      
      // Extract connection ID
      //int connectionId = WIFI_SERIAL.read () - 48; // subtract 48 because the read() function returns the ASCII decimal value and 0 (the first decimal number) starts at 48
      String connectionIdString    = lineString.substring (0, lineString.indexOf (','));
      int    connectionId          = connectionIdString.toInt ();
      String requestTypeString     = lineString.substring (lineString.indexOf (':') + 1, lineString.indexOf (' '));
      String requestResourceString = lineString.substring (lineString.indexOf (' ') + 1, lineString.lastIndexOf (' '));

      Serial.println ("Connection ID: " + String (connectionId));
      Serial.println ("Request type: " + requestTypeString);
      Serial.println ("Request resource: " + requestResourceString);
      Serial.println ();

      const char* requestType = requestTypeString.c_str ();
      const char* requestResource = requestResourceString.c_str ();
      char  content[128]; // Pointer to the request body's content.

      // Check if there's any body content in the POST request.
      if (strncmp (requestType, "POST", 5) == 0) {

        // Read the request line
        lineString = WIFI_SERIAL.readStringUntil ('\n');
        const char* line = lineString.c_str ();

        while (strncmp (line, "Content-Length:", 15) != 0) {
          // Serial.println ("\tSearching for \"Content-Length\"");

          lineString = WIFI_SERIAL.readStringUntil ('\n');
          const char* line = lineString.c_str ();
        }
        // Serial.println ("\tFound it.");

        // Extract "Content-Length" value
        char* headerValue   = strchr (line, ':') + 1;
        int   contentLength = atoi (headerValue); // Convert the "Content-Length" parameter to an integer.
        int   contentIndex = 0;

        // Extract the body content
        if (contentLength > 0) {
          if (WIFI_SERIAL.find ("\r\n\r\n")) { // Look for the beginning of the request's body.
            // Serial.println ("\tFound the body.");

            while (contentIndex < contentLength) {
  
              if (WIFI_SERIAL.available ()) {
                content[contentIndex] = WIFI_SERIAL.read ();
                contentIndex++;
  
                if (contentIndex >= contentLength) {
                  break;
                }
              }
            }
            content[contentIndex] = '\0';
          }
        }

        // Parse the request body's content
        // TODO: Parse the body based on the request.
      }

      // Handle request
      Handle_Request (connectionId, requestType, requestResource, content);
      
      String closeCommand = "AT+CIPCLOSE="; 
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";
      
      Send_Data (closeCommand, 3000, DEBUG);
    }
  }
}
