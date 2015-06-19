/*
This is basically stock code from Tmrh20 RF24 library examples. However, fixed Patch hardware is fixed and works with this library.

For now, one Patch must be connected to Serial on comp, to switch on transmission mode, default is receiving mode. 
"T" [enter] starts transmission, "R" [enter] reverts to receiving

*/

#include <SPI.h>
#include "RF24.h"

bool radioNumber = 1; // MUST MUST MUST change for different modules

const int boop = 2;
const int led = 3;

RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"}; //addresses

int role = 0;

byte counter = 1; // data to send

void setup(){
  
  //setting up pins
  
  pinMode(boop, INPUT);
  pinMode(led, OUTPUT);
  
  radio.begin();
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);        // Both radios listen on the same pipes by default, but opposite addresses
    radio.openReadingPipe(1,addresses[0]);      // Open a reading pipe on address 0, pipe 1
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  radio.startListening();                       // Start listening  
  radio.writeAckPayload(1,&counter,1);          // Pre-load an ack-paylod into the FIFO buffer for pipe 1
}

void loop(void) {

  if(digitalRead(boop)){
    role = 1;
    digitalWrite(led, HIGH);
  }
  else{
    role = 0;
    digitalWrite(led, LOW);
  }
  
  if (role == 1){

    byte gotByte; // ack response var
    
    radio.stopListening(); // to send out data, must stop listening    
    Serial.print(F("Now sending "));
    Serial.println(counter);
    
    unsigned long time = micros(); //records current time 
                                                            
    if ( radio.write(&counter,1) ){                         // Send the counter variable to the other radio 
        if(!radio.available()){                             // If nothing in the buffer, we got an ack but it is blank
            Serial.print(F("Got blank response. round-trip delay: "));
            Serial.print(micros()-time);
            Serial.println(F(" microseconds"));     
        }else{      
            while(radio.available() ){                      // If an ack with payload was received
                radio.read( &gotByte, 1 );                  // Read it, and display the response time
                unsigned long timer = micros();
                
                Serial.print(F("Got response "));
                Serial.print(gotByte);
                Serial.print(F(" round-trip delay: "));
                Serial.print(timer-time);
                Serial.println(F(" microseconds"));
                counter++; // increments data to be sent
            }
        }
    
    }
    else Serial.println(F("Sending failed.")); // if no ack respsonse
    delay(100);
    role = 0;
  }


/****************** Pong Back Role ***************************/

  if (role == 0) {
    
    radio.startListening();
    byte pipeNo, gotByte;
    while( radio.available(&pipeNo)){              // Read all available payloads
      radio.read( &gotByte, 1 );                   
                                                   // Since this is a call-response. Respond directly with an ack payload.
      gotByte += 1;                                // Ack payloads are much more efficient than switching to transmit mode to respond to a call
      radio.writeAckPayload(pipeNo,&gotByte, 1 );  // This can be commented out to send empty payloads.
      Serial.print(F("Loaded next response "));
      Serial.println(gotByte);
      
      digitalWrite(led, HIGH);
      delay(100);
   }
   
 }// end of if
 
}// end of loop
