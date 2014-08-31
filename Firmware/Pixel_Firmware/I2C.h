#ifndef I2C_H
#define I2C_H

#include "Behavior.h"
#include "Device.h"

#define I2C_MESSAGE_BYTE_SIZE 30
#define BUFFER_SIZE_I2C 32

char i2cMessageBuffer[128] = { 0 };
int i2cMessageBufferSize = 0;

// Message format:
// 00000000 00000000 00000000 00000000 00000000 00000000
// 
// Messages:
// - Pop next message
// - Clear all messages
// - Request top message (but don't remove it)
// - Remove top message (but don't send it, send removal status)

#define SLAVE_DEVICE_ADDRESS 2 // Slave device address

String getValue (String data, char separator, int index);
int getValueCount (String data, char separator);

// TODO: Move this to "Ports.h"
//void sendToSlave(char* text) {
//  // Send character string to slave device
//  Wire.beginTransmission(SLAVE_DEVICE_ADDRESS); // transmit to device #4
//  Wire.write(text);
//  Wire.endTransmission();    // stop transmitting
//}

// TODO: Move this to "Ports.h"
void syncPinValue(int pin) {

  // Get the most recent pin value
  int pinValue = getLastPinValue(pin);
  
  // Update the state (on slave board for Looper)
  char buf[8];
  Wire.beginTransmission(SLAVE_DEVICE_ADDRESS); // transmit to device #4
  Wire.write("pin ");
  Wire.write(itoa(pin, buf, 10)); // The pin number
  Wire.write(" ");
  Wire.write(pinValue == HIGH ? "1" : "0"); // The pin's value
  //  Wire.write(";");        // sends five bytes
  Wire.endTransmission();    // stop transmitting
  
  // TODO: Update state on other pixels in mesh network
  
  physicalPin[pin].isUpdated = false;
}

//int getPinValue2(int pin) {
//  
//  // TODO: Store current value on history stack (i.e., cache some locally, and store all of them in the cloud)
//  
//  // TODO: Update stored state of pin, so it can be updated only if needed, and its state can be queried, too (and transfered to another pixel).
//  // pinMode(pin, INPUT);
//  setPinMode (pin, PIN_MODE_INPUT);
//  
//  // Read to the pin
//  int value = digitalRead (pin);
//  
//  // Update the virtual Pixel's state
//  setPinValue (pin, (value == 1 ? PIN_VALUE_HIGH : PIN_VALUE_LOW));
//  
//  // Update the state
//  char buf[6]; // "-2147483648\0"
//  Wire.beginTransmission(SLAVE_DEVICE_ADDRESS); // transmit to device #4
//  Wire.write("pin ");
//  Wire.write(itoa(pin, buf, 10)); // The pin number
//  Wire.write(" ");
//  Wire.write(value == HIGH ? "1" : "0");
//  //  Wire.write(";");        // sends five bytes
//  Wire.endTransmission();    // stop transmitting 
//  
//  return value;
//}





char behaviorDescriptionBuffer[128];
int behaviorDescriptionBufferIndex = 0;

#define I2C_CONFIRM_UPDATE_STATE 1

/**
 * The "behavior" data structure and interpretter
 */
// TODO: Updates behavior (i.e., the state of the program being interpretted)
void Get_Behavior_Transformations () { // consider renaming this something like acceptBehaviorTransformation

//  Serial.println ("acceptBehaviorTransformations");
  
  // Request messages from slave
  // NOTE: This causes the function "requestEvent" specified in "Wire.onRequest(requestEvent);" 
  //       to be called on the slave device.
  int bytes = Wire.requestFrom (SLAVE_DEVICE_ADDRESS, I2C_MESSAGE_BYTE_SIZE); // Request 6 bytes from slave device #2
  
//  Serial.print ("bytes = "); Serial.println(bytes);

  // Receive messages from slave (if any)
  while (Wire.available () > 0) { // slave may send less than requested
  
    //char c = Wire.read (); // receive a byte as character
    char c = Wire.receive (); // receive a byte as character
//    Serial.print (c); // print the character
//    Serial.print(" ");
    
    // Copy byte into message buffer
    i2cMessageBuffer[i2cMessageBufferSize] = c;
    i2cMessageBufferSize++;
  }
  i2cMessageBuffer[i2cMessageBufferSize] = '\0'; // Terminate I2C message buffer
//  Serial.print("\n");

  i2cMessageBufferSize = 0; // Reset I2C message buffer size
  
  // Process received data (i.e., parse the received messages)
  if (strlen(i2cMessageBuffer) > 1) { // if (i2cMessageBufferSize > 0) {
//    Serial.println("Buffer > 1");

    // Search for start of message
    char* firstCharacterIndex = NULL;
    firstCharacterIndex = strchr (i2cMessageBuffer, '(');
    
    // Buffer the received message
    if (firstCharacterIndex != NULL) {
      Serial.println ("Found '('");
      firstCharacterIndex = firstCharacterIndex + 1;
      behaviorDescriptionBufferIndex = 0;
      
      // Find first of '\0', ')', or the (maximum) index of 32 (which means there should be more coming!)
      
//      strncpy (behaviorDescriptionBuffer + behaviorDescriptionBufferIndex, firstCharacterIndex + 1, );
    }
    
    boolean done = false;
    
    // Search for end of message
    char* lastCharacterIndex = NULL;
    lastCharacterIndex = strchr (i2cMessageBuffer, ')');
    
    // Update the last character index
    if (lastCharacterIndex != NULL) {
      Serial.println ("Found ')'");
      lastCharacterIndex = lastCharacterIndex - 1;
      done = true;
    } 
    
    // Search for the '\0' character if ')' not found
    if (lastCharacterIndex == NULL) {
      Serial.println ("Found '\0'");
      lastCharacterIndex = strchr (i2cMessageBuffer, '\0');
    }
    
    // Search for the last character in the message
    if (lastCharacterIndex == NULL) {
      Serial.print ("Found end of string at position "); Serial.print (BUFFER_SIZE_I2C); Serial.print ("\n");
      lastCharacterIndex = i2cMessageBuffer + BUFFER_SIZE_I2C;
    }
    
    // Copy the received data into the local buffer
    int behaviorDescriptionSize = lastCharacterIndex - firstCharacterIndex;
    strncpy (behaviorDescriptionBuffer + behaviorDescriptionBufferIndex, firstCharacterIndex, behaviorDescriptionSize);
    behaviorDescriptionBufferIndex = behaviorDescriptionBufferIndex + behaviorDescriptionSize;
    
    if (done) {
      Serial.println (behaviorDescriptionBuffer);
      
      String split = String (behaviorDescriptionBuffer);
      int spaceCount = getValueCount (split, ' ');
      
//      Serial.println (spaceCount);
//      
//      for (int i = 0; i < spaceCount; i++) {
//        
//        String value = getValue (split, ' ', i);
//        Serial.print (i);
//        Serial.print (" ");
//        Serial.print (value);
//        Serial.print (" ");
//        
//      }
//      Serial.print ("\n");

      String first = getValue (split, ' ', 0);
      
      if (first.compareTo ("create")) {
        
        String second = getValue (split, ' ', 1);
        
        if (first.compareTo ("substrate")) {
          // TODO: create substrate
          
          String uid = getValue (split, ' ', 2);
          
          // TODO: Create the substrate with the specified UID.
          
        } else if (first.compareTo ("behavior")) {
          
          // TODO: create behavior
          
        } else if (first.compareTo ("loop")) {
          
          // TODO: create loop
          
        } 
//        else if (first.compareTo ("line")) {
//          // TODO: Substrate
//        } else if (first.compareTo ("dot")) {
//          // TODO: Substrate
//        }
        
      }
      
    }
    
    
//    if (i2cMessageBuffer[0] == '(') { // if (i2cMessageBuffer[0] != '0') { // if (i2cMessageBuffer[0] == '(') {
////      Serial.println("Received message!");
//      Serial.println (i2cMessageBuffer);
      
      // TODO: Buffer the text after the '(' until reaching the ')'
      
      
    
//    // Split message by space
//    String split = String(i2cMessageBuffer); // "hi this is a split test";
//    
//    String statusSymbol = getValue(split, ' ', 0).toInt();
//      
//    if (statusSymbol.equals("1") == true) { // Check if status character is "1"
//    
//      Serial.println(i2cMessageBuffer);
//      
//      // Split message by space
//      // String split = String(i2cMessageBuffer); // "hi this is a split test";
//      
//      // Parse instruction message relayed by the "slave" device from "Looper"
//      int operation = getValue(split, ' ', 2).toInt();
//      
//      // Check operation and take handle it accordingly
//      if (operation == BEHAVIOR_ERASE) {
//        
//        eraseLoop();
//        
//      } else {
//      
//        // Parse behavior node's string form
//        int index     = getValue(split, ' ', 1).toInt();
//        int pin       = getValue(split, ' ', 3).toInt();
//        int type      = getValue(split, ' ', 4).toInt();
//        // int mode      = getValue(split, ' ', 3).toInt();
//        int value     = getValue(split, ' ', 5).toInt();
//        
//        // TODO: Create node object from parsed data (i.e., "Behavior behavior = deserializeBehavior();").
//        // TODO: Add node object to queue (i.e., the program) (i.e., "appendBehavior(behavior);")
//        //appendLoopNode(pin, operation, type, value);
//        applyBehaviorTransformation(index, pin, operation, type, value);
//        
//      }
//    }
//  }

//  i2cMessageBufferSize = 0; // Reset I2C message buffer size
//  
//  // Process received data (i.e., parse the received messages)
//  if (strlen(i2cMessageBuffer) > 1) { // if (i2cMessageBufferSize > 0) {
//    
//    // Split message by space
//    String split = String(i2cMessageBuffer); // "hi this is a split test";
//    
//    String statusSymbol = getValue(split, ' ', 0).toInt();
//      
//    if (statusSymbol.equals("1") == true) { // Check if status character is "1"
//    
//      Serial.println(i2cMessageBuffer);
//      
//      // Split message by space
//      // String split = String(i2cMessageBuffer); // "hi this is a split test";
//      
//      // Parse instruction message relayed by the "slave" device from "Looper"
//      int operation = getValue(split, ' ', 2).toInt();
//      
//      // Check operation and take handle it accordingly
//      if (operation == BEHAVIOR_ERASE) {
//        
//        eraseLoop();
//        
//      } else {
//      
//        // Parse behavior node's string form
//        int index     = getValue(split, ' ', 1).toInt();
//        int pin       = getValue(split, ' ', 3).toInt();
//        int type      = getValue(split, ' ', 4).toInt();
//        // int mode      = getValue(split, ' ', 3).toInt();
//        int value     = getValue(split, ' ', 5).toInt();
//        
//        // TODO: Create node object from parsed data (i.e., "Behavior behavior = deserializeBehavior();").
//        // TODO: Add node object to queue (i.e., the program) (i.e., "appendBehavior(behavior);")
//        //appendLoopNode(pin, operation, type, value);
//        applyBehaviorTransformation(index, pin, operation, type, value);
//        
//      }
//    }
  }
}

///**
// * The "behavior" data structure and interpretter
// */
//// TODO: Updates behavior (i.e., the state of the program being interpretted)
//void acceptBehaviorTransformations() { // consider renaming this something like acceptBehaviorTransformation
//
////  Serial.println ("acceptBehaviorTransformations");
//  
//  // Request messages from slave
//  // NOTE: This causes the function "requestEvent" specified in "Wire.onRequest(requestEvent);" 
//  //       to be called on the slave device.
//  int bytes = Wire.requestFrom(SLAVE_DEVICE_ADDRESS, I2C_MESSAGE_BYTE_SIZE); // Request 6 bytes from slave device #2
//  
////  Serial.print ("bytes = "); Serial.println(bytes);
//
//  // Receive messages from slave (if any)
//  while (Wire.available () > 0) { // slave may send less than requested
//  
//    //char c = Wire.read (); // receive a byte as character
//    char c = Wire.receive (); // receive a byte as character
////    Serial.print (c); // print the character
////    Serial.print(" ");
//    
//    // Copy byte into message buffer
//    i2cMessageBuffer[i2cMessageBufferSize] = c;
//    i2cMessageBufferSize++;
//  }
//  i2cMessageBuffer[i2cMessageBufferSize] = '\0'; // Terminate I2C message buffer
////  Serial.print("\n");
//
//  i2cMessageBufferSize = 0; // Reset I2C message buffer size
//  
//  // Process received data (i.e., parse the received messages)
//  if (strlen(i2cMessageBuffer) > 1) { // if (i2cMessageBufferSize > 0) {
//    Serial.println("Buffer > 1");
//    
//    if (i2cMessageBuffer[0] != '0') { // if (i2cMessageBuffer[0] == '(') {
////      Serial.println("Received message!");
//      Serial.println (i2cMessageBuffer);
//    }
//    
////    // Split message by space
////    String split = String(i2cMessageBuffer); // "hi this is a split test";
////    
////    String statusSymbol = getValue(split, ' ', 0).toInt();
////      
////    if (statusSymbol.equals("1") == true) { // Check if status character is "1"
////    
////      Serial.println(i2cMessageBuffer);
////      
////      // Split message by space
////      // String split = String(i2cMessageBuffer); // "hi this is a split test";
////      
////      // Parse instruction message relayed by the "slave" device from "Looper"
////      int operation = getValue(split, ' ', 2).toInt();
////      
////      // Check operation and take handle it accordingly
////      if (operation == BEHAVIOR_ERASE) {
////        
////        eraseLoop();
////        
////      } else {
////      
////        // Parse behavior node's string form
////        int index     = getValue(split, ' ', 1).toInt();
////        int pin       = getValue(split, ' ', 3).toInt();
////        int type      = getValue(split, ' ', 4).toInt();
////        // int mode      = getValue(split, ' ', 3).toInt();
////        int value     = getValue(split, ' ', 5).toInt();
////        
////        // TODO: Create node object from parsed data (i.e., "Behavior behavior = deserializeBehavior();").
////        // TODO: Add node object to queue (i.e., the program) (i.e., "appendBehavior(behavior);")
////        //appendLoopNode(pin, operation, type, value);
////        applyBehaviorTransformation(index, pin, operation, type, value);
////        
////      }
////    }
//  }
//
////  i2cMessageBufferSize = 0; // Reset I2C message buffer size
////  
////  // Process received data (i.e., parse the received messages)
////  if (strlen(i2cMessageBuffer) > 1) { // if (i2cMessageBufferSize > 0) {
////    
////    // Split message by space
////    String split = String(i2cMessageBuffer); // "hi this is a split test";
////    
////    String statusSymbol = getValue(split, ' ', 0).toInt();
////      
////    if (statusSymbol.equals("1") == true) { // Check if status character is "1"
////    
////      Serial.println(i2cMessageBuffer);
////      
////      // Split message by space
////      // String split = String(i2cMessageBuffer); // "hi this is a split test";
////      
////      // Parse instruction message relayed by the "slave" device from "Looper"
////      int operation = getValue(split, ' ', 2).toInt();
////      
////      // Check operation and take handle it accordingly
////      if (operation == BEHAVIOR_ERASE) {
////        
////        eraseLoop();
////        
////      } else {
////      
////        // Parse behavior node's string form
////        int index     = getValue(split, ' ', 1).toInt();
////        int pin       = getValue(split, ' ', 3).toInt();
////        int type      = getValue(split, ' ', 4).toInt();
////        // int mode      = getValue(split, ' ', 3).toInt();
////        int value     = getValue(split, ' ', 5).toInt();
////        
////        // TODO: Create node object from parsed data (i.e., "Behavior behavior = deserializeBehavior();").
////        // TODO: Add node object to queue (i.e., the program) (i.e., "appendBehavior(behavior);")
////        //appendLoopNode(pin, operation, type, value);
////        applyBehaviorTransformation(index, pin, operation, type, value);
////        
////      }
////    }
////  }
//}




/**
 * TODO: Move this to "Loop.h" (and/or break it down into "Behavior.h")
 */
void behaviorLoopStep() {
  
  if (loopSize > 0) {
    Behavior* currentBehavior = &behaviorLoop[loopCounter]; // Get current behavior
    
    boolean sustainCounter = false; // Should the counter stay the same this iteration?
    
    // Interpret the behavior
    
    // NOTE: right now, assuming the instruction type... pin I/O
    
//    Serial.println((*currentBehavior).pin);
//    Serial.println((*currentBehavior).value);
    
    if (true) { // if ((*currentBehavior).instructionType [equals] "pin I/O") 
    
      if ((*currentBehavior).operation == PIN_READ_DIGITAL) { // Read pin state
        
        //int pinValue = getPinValue2((*currentBehavior).pin);
        int pinValue = getPinValue((*currentBehavior).pin);
        syncPinValue((*currentBehavior).pin);
        Serial.println("PIN_READ_DIGITAL");
      
      } else if ((*currentBehavior).operation == PIN_WRITE_DIGITAL) { // Write to pin

        // setPinValue((*currentBehavior).pin, ((*currentBehavior).value == 1 ? HIGH : LOW));
        setPinValue((*currentBehavior).pin, (*currentBehavior).value);
        syncPinValue((*currentBehavior).pin);
        Serial.println("PIN_WRITE_DIGITAL");
        
      } else if ((*currentBehavior).operation == BEHAVIOR_DELAY) {
        
        // Set up timer
        Delay* currentDelay = NULL;
        for (int i = 0; i < delayCount; i++) {
          if (delays[i].behavior == currentBehavior) {
//            Serial.println("Found delay"); Serial.print("\t"); Serial.print(i); Serial.print("\n");
            currentDelay = &delays[i];
          }
        }
        if (currentDelay != NULL) {
          unsigned long currentTime = millis();
//          Serial.println(currentTime);
//          Serial.println((*currentDelay).startTime);
//          Serial.println((*currentDelay).duration);
//          Serial.println(currentTime - (*currentDelay).startTime);
          // Set up start time if it's been reset (i.e., if it is zero)
          if ((*currentDelay).startTime == 0) {
            (*currentDelay).startTime = currentTime;
          }
          
          // Check if delay has passed
          if (currentTime - (*currentDelay).startTime < (*currentDelay).duration) {
            sustainCounter = true;
          } else {
            (*currentDelay).startTime = currentTime; // Update the start time of the delay
            (*currentDelay).startTime = 0; // Reset timer (because it expired)
//            sustainCounter = false;
          }
        }
//        delays[delayCount].startTime = millis();
//        delays[delayCount].duration = 1000;
//        delays[delayCount].behavior = currentBehavior;
//        delayCount++;

        if (sustainCounter == false) {
          Serial.println("DELAY");
        }
        
      } else if ((*currentBehavior).operation == BEHAVIOR_ERASE) {
        
        Serial.println("ERASE");
          
//        int milliseconds = 1000;
//        delay(milliseconds);
        
      }
    }
    
    if (!sustainCounter) {
      // Advance the loop behavior counter
      if (loopSize == 0) {
        loopCounter = 0;
      }
      loopCounter = (loopCounter + 1) % loopSize; // Increment loop counter
    }
    
    
    // Serial.print(".");
  }
}

String getValue (String data, char separator, int index) {
  
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
        found++;
        strIndex[0] = strIndex[1] + 1;
        strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring (strIndex[0], strIndex[1]) : "";
}

int getValueCount (String data, char separator) {
  
  int count = 0;
  int maxIndex = data.length() - 1;

  for (int i = 0; i < data.length (); i++) {
    if (data.charAt(i) == separator) {
      count++;
    }
  }
  
  if (count > 0) {
    count = count + 1;
  }

  return count;
}

#endif