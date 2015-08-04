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
 
void loop() {
  
  if (WIFI_SERIAL.available ()) { // check if the esp is sending a message
    
    if (WIFI_SERIAL.find ("+IPD,")) {
      
     delay (1000);
 
     int connectionId = WIFI_SERIAL.read () - 48; // subtract 48 because the read() function returns the ASCII decimal value and 0 (the first decimal number) starts at 48
     
     String webpage = "<html><h1>Clay</h1><button>LED1</button></html>";
 
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend += webpage.length();
     cipSend += "\r\n";
     
     Send_Data (cipSend, 1000, DEBUG);
     Send_Data (webpage, 1000, DEBUG);
     
     webpage = "<button>LED2</button>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend += webpage.length ();
     cipSend += "\r\n";
     
     Send_Data (cipSend, 1000, DEBUG);
     Send_Data (webpage, 1000, DEBUG);
 
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
