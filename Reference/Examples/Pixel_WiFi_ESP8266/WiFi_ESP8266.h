#ifndef WIFI_ESP8266
#define WIFI_ESP8266

// Resources:
// http://wiki.iteadstudio.com/ESP8266_Serial_WIFI_Module
// https://forum.pjrc.com/threads/27850-A-Guide-To-Using-ESP8266-With-TEENSY-3
// https://github.com/espressif/esp8266_at/wiki/at_example_0020000903
// http://www.electrodragon.com/w/ESP8266#Documents
// http://uzebox.org/wiki/index.php?title=ESP8266_AT_Commands
// http://www.pridopia.co.uk/pi-doc/ESP8266ATCommandsSet.pdf
// https://github.com/espressif/esp8266_at/wiki/AT_Description

#define WIFI_SERIAL Serial1
#define WIFI_BAUD_RATE 115200

// Sets up the Wi-Fi electronic circuit components (ESP8266)
void Setup_WiFi () {
  WIFI_SERIAL.begin (WIFI_BAUD_RATE);
  
  // TODO:
  // - Reset the ESP8266
  // - Wait briefly for the WiFi module to bootup (<= 800 ms)
  // - Poll the module with "AT" command looking for the response "OK"
}

// Resets the Wi-Fi module and checks if it responds as "ready".
// Uses: AT+RST
void Verify_WiFi () {
  // Test if the module is ready
  WIFI_SERIAL.println ("AT+RST");
  delay (1000);
  if (WIFI_SERIAL.find ("ready")) {
    Serial.println ("Module is ready");
  } else {
    Serial.println ("Module have no response.");
    while (1);
  }
  delay (1000);
}

// Checks the firmware type and versions.
// Uses: AT+GMR
void WiFi_Check_Firmware () {
  WIFI_SERIAL.println ("AT+GMR");
}

// Repeatedly try to connect to the WiFi
// Uses: AT+CIPMUX=0
void Strong_Connect_To_Access_Point (int retryCount) {
  boolean connected = false;
  for (int i = 0; i < retryCount; i++) {
    if (Connect_To_Access_Point ()) {
      connected = true;
      break;
    }
  }
  if (!connected) {
    while (1);
  }
  delay (5000);
  
  //print the ip addr
  /*Serial1.println("AT+CIFSR");
  Serial.println("ip address:");
  while (Serial1.available())
    Serial.write(Serial1.read());*/
  //set the single connection mode
  WIFI_SERIAL.println ("AT+CIPMUX=0");
}

// Connects to the “shell-2.4GHz” access point with password “technologydrive”.
// Uses: AT+CWJAP=”shell-2.4GHz”,”technologydrive”
// Modes: 1 = Station (STA), 2 = Access Point (AP), 3 = Both. STA is the default mode of a router. AP is a normal mode for devices.
boolean Connect_To_Access_Point (String ssid, String password) {
  // Serial1.println ("AT+CWMODE=1");
  WIFI_SERIAL.println ("AT+CWMODE=3");
  String cmd = "AT+CWJAP=\"";
  cmd += ssid;
  cmd += "\",\"";
  cmd += ;
  cmd += "\"";
  Serial.println (cmd);
  WIFI_SERIAL.println (cmd);
  delay (10000);
  if (WIFI_SERIAL.find ("OK")) {
    Serial.println ("OK, Connected to WiFi.");
    return true;
  } else {
    Serial.println ("Can not connect to the WiFi.");
    return false;
  }
}

// Resets the Wi-Fi module.
// Uses: AT+RST
void WiFi_Reset () {
  WIFI_SERIAL.println ("AT+RST");
}

// Change the working mode of the device (to AP+STA).
// Uses: AT+CWMODE=3
void WiFi_Set_Mode (int mode) {
  WIFI_SERIAL.println ("AT+CWMODE=3");
}

// Lists the available Wi-Fi access points. The "LAP" means "list access points".
// Uses: AT+CWLAP
void WiFi_Get_Access_Points () {
  WIFI_SERIAL.println ("AT+CWLAP");
}

// Lists the IP address.
// Uses: AT+CIFSR
void WiFi_Get_IP_Address () {  
  WIFI_SERIAL.println ("AT+CIFSR");
}

// Disconnects from the access point.
// Uses: AT+CWQAP ("quit access point")
void WiFi_Disconnect () {
  WIFI_SERIAL.println ("AT+CWQAP");
}

// Sends and HTTP request to a server.
//
// Uses:
// AT+CIPMUX=1
// AT+CIPSTART="TCP","looper.cc", 80
// AT+CIPSEND={byte length of GET request string below}
// {wait for ">" string to be returned by ESP8266}
// GET / HTTP/1.0\r\n\r\n
//
// References:
// - RFC2616 HTTP/1.1 Header Field Definitions
//   www.w3.org/Protocols/rfc2616/rfc2616-sec14.html
// - List of HTTP Header Fields
//   https://en.wikipedia.org/wiki/List_of_HTTP_header_fields
void WiFi_HTTP_GET_Request () {
  WIFI_SERIAL.println ("AT+CIPMUX=1"); // 0 = single connection, 1 = multiple connection
  
  // Establish a TCP connection as a client.
  // Format: AT+CIPSTART=id,type,addr,port
  WIFI_SERIAL.println ("AT+CIPSTART=4,\"TCP\",\"looper.cc\",80"); // =channel_id,connection_protocol,address,port
  
  // delay (300); // Wait a little while for the 'Linked' response.
  
  // Prepare the GET request.
  String cmd = "GET /status.html HTTP/1.0\r\n";
  cmd += "Host: looper.cc\r\n"; // NOTE: The "Host" field is mandatory since HTTP/1.1.
  cmd += "\r\n"; // Add a second consecutive "\r\n" to indicate end of HTTP request.
  
  // Start sending HTTP request. To do so, start by sending the channel ID and number of bytes in the HTTP request.
  WIFI_SERIAL.print ("AT+CIPSEND=");
  WIFI_SERIAL.print ("4"); // channel_id (NOTE: This is only needed if mutiple connections have been enabled with AT+CIPMUX=1.)
  WIFI_SERIAL.print (",");
  WIFI_SERIAL.print (cmd.length ()); // HTTP request byte count (i.e., the byte size of the request)
  WIFI_SERIAL.println ();
  
  // Look for the ">" prompt from the ESP8266, returned if the AT+CIPSEND command was successful.
  if (Serial.find (">")) {
    
    // The connection was established, so send the request data.
    
    // Send the HTTP GET request data prepared above over the TCP connection.
    Serial.println (cmd);
    
  } else {
    // Something went wrong, so close the connection.
    Serial.println ("AT+CIPCLOSE");
  }
  
  // Check the returned HTTP header and data (e.g., the data could be a web page).
  // Looking for a keyword. I used COLLIDER_ONLINE
  if (Serial.find ("COLLIDER_ONLINE")) {
    // If the string was found we know the page is up (i.e., success). Parse the response and perform "success" behavior.
    
    // TODO: Parse the request response.
    
  } else {
    // The string was not found, so assume the server is offline.
    
    // TODO: Handle "request error".
    Serial.println ("ESP8266 Error: Failure to find expected string in HTTP request response.");
    
  }
  
  // Wait a second for everything to settle.
  delay (1000);
  
  // Close the TCP connection.
  Serial.println("AT+CIPCLOSE");
}

// Request methods: GET, HEAD, POST, PUT, DELETE, TRACE, OPTIONS, CONNECT, PATCH (from https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol)
// TODO: void WiFi_HTTP_OPTIONS_Request ()
// TODO: void WiFi_HTTP_POST_Request ()
// TODO: void WiFi_HTTP_DELETE_Request ()

// HTTP Server:

void Start_HTTP_Server () {
}

void Receive_HTTP_Request () {
}

// UDP Server:

void Start_UDP_Server (int port) {
}

void Send_UDP_Message () {
}

void 

#endif
