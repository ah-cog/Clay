//#include <SoftwareSerial1.h>
#define SSID        "Arbor Guest" // "AWS" // "joopal" // "HOME-5EE4" // "shell-2.4GHz"
#define PASS        "Nouakchott" // "Codehappy123" // "Cassandra2048" // "316793944D3C0868" // "technologydrive"
#define DST_IP      "220.181.111.85"    //baidu.com
//SoftwareSerial dbgSerial(10, 11); // RX, TX
void setup()
{
  delay (1000);

  pinMode (3, OUTPUT); // Wi-Fi: ESP8266 breakout CH_PD (chip enable on ESP8266 IC)
  pinMode (4, OUTPUT); // Wi-Fi: ESP8266 breakout RST (reset on ESP8266 IC)
  pinMode (5, OUTPUT); // Wi-Fi: ESP8266 breakout GPIO0 (reset on ESP8266 IC)
  pinMode (8, OUTPUT); // Wi-Fi: ESP8266 breakout GPIO0 (reset on ESP8266 IC)

  digitalWrite (5, HIGH); // Set up GPIO0. "At boot: low causes bootloader to enter flash upload mode; high causes normal boot" (from http://www.esp8266.com/wiki/doku.php?id=esp8266-module-family)
  digitalWrite (8, HIGH); // Set up GPIO2 in Working Mode
  digitalWrite (3, HIGH); // Set up CH_PD to enable the chip
  digitalWrite (4, HIGH); // Set up RST

  delay (1000);
  
  // Open serial communications and wait for port to open:
  delay(5000);
//  Serial1.setTimeout(5000);
  Serial.begin(115200);  //can't be faster than 19200 for softserial
  Serial1.begin(9600); // Serial1.begin(115200);
  Serial.println("ESP8266 Demo");
  //test if the module is ready
  Serial1.println("AT+RST");
  delay(1000);
  if (Serial1.find("OK")) // if (Serial1.find("ready"))
  {
    Serial.println("Module is ready");
  }
  else
  {
    Serial.println("Module have no response.");
    while (1);
  }
  delay(1000);
  //connect to the wifi
  boolean connected = false;
  for (int i = 0; i < 5; i++)
  {
    if (connectWiFi())
    {
      connected = true;
      break;
    }
  }
  if (!connected) {
    while (1);
  }
  delay(5000);
  //print the ip addr
  /*Serial1.println("AT+CIFSR");
  Serial.println("ip address:");
  while (Serial1.available())
    Serial.write(Serial1.read());*/
  //set the single connection mode
  Serial1.println("AT+CIPMUX=0");
}
void loop()
{
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += DST_IP;
  cmd += "\",80";
  Serial1.println(cmd);
  Serial.println(cmd);
  if (Serial1.find("Error")) return;
  cmd = "GET / HTTP/1.0\r\n\r\n";
  Serial1.print("AT+CIPSEND=");
  Serial1.println(cmd.length());
  delay(2000); // Delay a little bit to wait for a response from the website.
  if (Serial1.find(">")) {
    Serial.print(">");
  } else {
    Serial1.println("AT+CIPCLOSE");
    Serial.println("connect timeout");
    delay(1000);
    return;
  }
  Serial1.print(cmd);
  delay(2000);
  //Serial1.find("+IPD");
  while (Serial1.available())
  {
    char c = Serial1.read();
    Serial.write(c);
    if (c == '\r') Serial.print('\n');
  }
  Serial.println("====");
  delay(1000);
}
boolean connectWiFi()
{
  //Serial1.println("AT+CWMODE=1");
  Serial1.println("AT+CWMODE=3");
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  Serial.println(cmd);
  Serial1.println(cmd);
  delay(10000);
  if (Serial1.find("OK"))
  {
    Serial.println("OK, Connected to WiFi.");
    return true;
  } else
  {
    Serial.println("Can not connect to the WiFi.");
    return false;
  }
}
