#include <Wire.h>
#include <LSM303.h>

LSM303 compass;
int i = 0;
int x = 0;
int y = 0;
int z = 0;
int led = 13;
int flag = 1;

char report[80];

void setup() {
  
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();

}

void loop() {
  
  if(flag == 1){
    for(i = 0; i<10; i++){
      compass.read();
      x+=compass.a.x;
      y+=compass.a.y;
      z+=compass.a.z;
    }
    x = x/10;
    y = y/10;
    z = z/10;
    flag = 0;
    delay(100);
  }
  
  compass.read();
  if(x-compass.a.x > 2500 || y-compass.a.y > 2500 || z-compass.a.z > 2500){
    digitalWrite(led, HIGH);
    delay(50);
    flag = 1;
  }
  else digitalWrite(led, LOW);
  
  Serial.println(compass.a.x);
  


}
