/*
This is basically stock code from Tmrh20 RF24 library examples. However, fixed Patch hardware is fixed and works with this library.

For now, one Patch must be connected to Serial on comp, to switch on transmission mode, default is receiving mode. 
"T" [enter] starts transmission, "R" [enter] reverts to receiving

*/

#include <SPI.h>
#include "RF24.h"

bool radioNumber = 1; // MUST MUST MUST change for different modules

RF24 radio(9,10);

byte addresses[][6] = {"1Node","2Node"}; //addresses

typedef enum { role_ping_out = 1, role_pong_back } role_e;                 // The various roles supported by this sketch
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};  // The debug-friendly names of those roles
role_e role = role_pong_back;                                              // The role of the current running sketch

byte counter = 1; // data to send

void setup(){
  
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
  
  delay(3000);
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted_CallResponse"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  delay(3000);
  
}

void loop(void) {

  if (role == role_ping_out){

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
    
    delay(1000);  // Try again later
  }


/****************** Pong Back Role ***************************/

  if ( role == role_pong_back ) {
    byte pipeNo, gotByte;
    while( radio.available(&pipeNo)){              // Read all available payloads
      radio.read( &gotByte, 1 );                   
                                                   // Since this is a call-response. Respond directly with an ack payload.
      gotByte += 1;                                // Ack payloads are much more efficient than switching to transmit mode to respond to a call
      radio.writeAckPayload(pipeNo,&gotByte, 1 );  // This can be commented out to send empty payloads.
      Serial.print(F("Loaded next response "));
      Serial.println(gotByte);  
   }
 }


  if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == role_pong_back ){      
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      role = role_ping_out;  // Become the primary transmitter (ping out)
      counter = 1;
   }else
    if ( c == 'R' && role == role_ping_out ){
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));      
       role = role_pong_back; // Become the primary receiver (pong back)
       radio.startListening();
       counter = 1;
       radio.writeAckPayload(1,&counter,1);
       
    }
  }
}
