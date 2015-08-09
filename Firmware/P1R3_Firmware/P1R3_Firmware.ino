#define DEBUG true

#define WIFI_SERIAL      Serial1
#define WIFI_SERIAL_BAUD 115200
#define WIFI_SSID        "clay-2.4ghz" // "Jackson 5" // "HOME-5EE4" // "joopal" // "AWS" // "shell-2.4GHz"
#define WIFI_PASS        "goldenbrown" // "tigertiger" // "316793944D3C0868" // "Cassandra2048" // "Codehappy123" // "technologydrive"
#define HTTP_SERVER_PORT "80"          // using port 8080 by default

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];

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

#include <stdarg.h>

#define PIN_COUNT 8
int pinAddresses[PIN_COUNT];
int pinModes[PIN_COUNT]; // 0=NONE, 1=INPUT, 2=OUTPUT
int pinValues[PIN_COUNT];

void Setup_Pins (int n_args, ...) {

  // Assign physical MCU pins to Clay's I/O
  va_list ap;
  va_start (ap, n_args);
  for (int i = 0; i < n_args; i++) {
    pinAddresses[i] = va_arg (ap, int);
  }
  va_end (ap);
  
}

void Set_Pin (int number, int mode, int value) {
  Serial.println ("Set_Pin");
  pinModes[(pinAddresses[number])] = mode;
  pinMode (pinAddresses[number], mode);
  
  Serial.println ("number = " + String (number));
  Serial.println ("pinAddresses[number] = " + String (pinAddresses[number]));
  Serial.println ("pinModes[(pinAddresses[number])] = " + String (pinModes[(pinAddresses[number])]));

  if (pinModes[(pinAddresses[number])] == OUTPUT) {
    pinValues[(pinAddresses[number])] = value;
    digitalWrite (pinAddresses[number], pinValues[(pinAddresses[number])]);
  }
}

int Get_Pin_Address (int number) {
  return pinAddresses[number];
}

int Get_Pin_Mode (int number) {
  return pinModes[number];
}

int Get_Pin_Value (int number) {

  if (pinModes[(pinAddresses[number])] == INPUT) {
    pinValues[(pinAddresses[number])] = digitalRead (pinAddresses[number]);
    return pinValues[(pinAddresses[number])];
  } else if (pinModes[(pinAddresses[number])] == OUTPUT) {
    return pinValues[(pinAddresses[number])];
  }

  return -1;
}

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
