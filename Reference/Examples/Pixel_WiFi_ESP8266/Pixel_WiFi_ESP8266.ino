#include <Wire.h>
//#include <SoftwareSerial.h>
//#include <Adafruit_CC3000.h>
//#include <SPI.h>

#include "WiFi_ESP8266.h"

#define WIFI_SSID "joopal" // "AWS"
#define WIFI_PASSWORD "Cassandra2048" // "Codehappy123"

void setup () {
  
  delay (1000);
  Serial.begin(9600);
  
  WiFi_Setup ();
}

// AT+CIPSTART="TCP","looper.cc",80
// AT+CIPSEND=18
// GET / HTTP/1.1
// Host: looper.cc
// User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.124 Safari/537.36
// --- OR ---
// AT+CIPSEND=43
// GET / HTTP/1.1\r\nUser-Agent: curl/7.37.0\r\n\r\n
// --- OR ---
// AT+CIPSEND=33
// GET / HTTP/1.1\r\nHost: looper.cc\r\n\r\n

// AT+CIPSTART="TCP","192.168.18.196",3000
// 


void loop () {
  
  WIFI_SERIAL.println ("AT+RST");
  
  delay (2000);
  
  // Connect to Wi-Fi hotspot
  Serial.println ("> Connecting to Wi-Fi access point...");
  Connect_To_Access_Point (WIFI_SSID, WIFI_PASSWORD);
  
  // Get IP Address
//  Serial.println ("> Getting IP address of device...");
//  WiFi_Get_IP_Address ();
  
  delay (2000);
  
  // AT+CIPSTART="TCP","cn.bing.com",80
  // GET / HTTP/1.1\r\nUser-Agent: curl/7.37.0\r\nHost: %s\r\nAccept: */*\r\n\r\n
  // e.g., GET / HTTP/1.1\r\nUser-Agent: curl/7.37.0\r\nHost: cn.bing.com\r\nAccept: */*\r\n\r\n
  
  String address = "cn.bing.com";
  String port = 80;
  String request = "GET / HTTP/1.1\r\nUser-Agent: curl/7.37.0\r\nHost: " + address + "\r\nAccept: */*\r\n\r\n";
  
  Serial.println ("Connecting to " + address);
  WIFI_SERIAL.println ("AT+CIPSTART=\"TCP\",\"" + address +  "\"," + port + "");
  delay (5000);
  Serial.println();
  // Possible outcomes for AT+CIPSTART:
  // - "ALREAY CONNECT" (yes, there's a typo)
  
  int requestBufferMaxSize = 512;
  char requestChars[requestBufferMaxSize];
  Serial.println ("Sending " + String (request.length ()) + " bytes:");
  Serial.println (request);
  WIFI_SERIAL.print ("AT+CIPSEND=" + request.length ());
  delay (4000);
  request.toCharArray (requestChars, requestBufferMaxSize);
  WIFI_SERIAL.print (requestChars);
  
  
  
  
  
  while (true) {
    /* send everything received from the hardware uart to usb serial & vv */
    if (Serial.available() > 0) {
      char ch = Serial.read();
      Serial1.print(ch);
    }
    if (Serial1.available() > 0) {
      char ch = Serial1.read();
      Serial.print(ch);
    }
  }
}

// NOTE: The following code bridges the Serial communications between the console and the Wi-Fi chip, providing direct terminal to the Wi-Fi chip.
//
//void setup()
//{
//  delay(5000); // Add a delay for the device to stabalize
//  Serial.begin(9600);
//  Serial1.begin(9600);
//}
//
//void loop()
//{
//  /* send everything received from the hardware uart to usb serial & vv */
//  if (Serial.available() > 0) {
//    char ch = Serial.read();
//    Serial1.print(ch);
//  }
//  if (Serial1.available() > 0) {
//    char ch = Serial1.read();
//    Serial.print(ch);
//  }
//}
