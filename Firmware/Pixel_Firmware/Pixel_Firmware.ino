/*
  "Pixel" Firmware (for Gestural Language), Rendition 2
  
  Creator: Michael Gubbels

  "The reasonable man adapts himself to the world;
   the unreasonable one persists in trying to adapt the world to himself.
   Therefore all progress depends on the unreasonable man."
   
   - George Bernard Shaw
     Man and Superman (1903) "Maxims for Revolutionists"

*/

#include <EEPROM.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <SPI.h>

String ipAddress = "unassigned";

#include <Adafruit_NeoPixel.h>
#include "Utilities.h"
#include "Platform.h"
#include "Color.h"
#include "Sound.h"
#include "Motion.h"

#include "Gesture.h"
#include "Movement.h"
#include "Communication.h"
#include "Looper.h"
#include "I2C.h"
#include "Ports.h"

#include "Foundation.h" // i.e., the kernel
#include "Language.h" // i.e., the shell

/**
 * Module configuration
 */

//            _               
//           | |              
//   ___  ___| |_ _   _ _ __  
//  / __|/ _ \ __| | | | '_ \ 
//  \__ \  __/ |_| |_| | |_) |
//  |___/\___|\__|\__,_| .__/ 
//                     | |    
//                     |_|    

void setup () {
  
//  delay (2000);
  
//  Serial.println ("Pixel!");
  
  // Initialize pseudorandom number generator
  randomSeed (analogRead (0));
  
  setupCommunication ();
  setupBridge ();
  
  if (hasFoundationUuid == false) {
    setupFoundation ();
    hasFoundationUuid = true;
  } // The layer on which the "platform" depends
  
  setupLooper (); // Setup the Looper engine.
  
  setupPlatformUuid ();
//  setupPlatform(); // Setup Pixel's reflection (i.e., it's virtual machine)
  setupPorts (); // Setup pin mode for I/O
  setupColor (); // Setup the Pixel's color
  
  // TODO: Read device GUID from EEPROM if it exists, otherwise generate one, store it in EEPROM, and read it.

  // Initialize module's color
  //setModuleColor(random(256), random(256), random(256)); // Set the module's default color
  Update_Module_Color (255, 255, 255);
  
  // Assign the module a unique color
  Update_Color (defaultModuleColor[0], defaultModuleColor[1], defaultModuleColor[2]);
  
  delay (2000);
  
  Serial.begin (115200); 
  Serial.println (F ("Pixel Firmware"));
  
  setupPlatform (); // Setup Pixel's reflection (i.e., it's virtual machine)
  
  // Setup physical orientation sensing peripherals (i.e., IMU)
  setupOrientationSensing ();
  setupGestureSensing ();

  // Setup sound
  setupSound ();
  
  // Flash RGB LEDs
  Blink_Light (3);
  
  
  Move_Motion (0.5 * 1000);
  
//  Serial.print ("Foundation UUID: "); for (int i = 0; i < UUID_SIZE; i++) { Serial.print ((char) foundationUuid[i]); } Serial.print ("\n");
}

//   _                   
//  | |                  
//  | | ___   ___  _ __  
//  | |/ _ \ / _ \| '_ \ 
//  | | (_) | (_) | |_) |
//  |_|\___/ \___/| .__/ 
//                | |    
//                |_|    

boolean hasGestureProcessed = false;

void loop () {
  
  Get_Console ();
  
  // Broadcast Presence
  if (hasPlatformUuid) { 

    // Broadcast device's address (UUID)
    unsigned long currentTime = millis ();
    if (currentTime - lastBroadcastTime > broadcastTimeout) {
      
//      if (isReading == false) {
//        isWriting = true;

        // MESH_SERIAL.write ('!');
//        String data = String ("{ uuid: ") + String (platformUuid) + String (" , type: 'keep-alive' }");
//        const int serialBufferSize = 64;
//        char charData[serialBufferSize];
//        data.toCharArray (charData, serialBufferSize);
        
        int bytesSent = 0;
        String data = "";
        if (classifiedGestureIndex != previousClassifiedGestureIndex) {
          data = String ("(") + String (BROADCAST_ADDRESS) + String (", ") + String (platformUuid) + String (", ") + String (ANNOUNCE_POOF) + String (")");
          const int serialBufferSize = 64;
          char charData[serialBufferSize];
          data.toCharArray (charData, serialBufferSize);
          bytesSent = MESH_SERIAL.write (charData);
        }
        
//        Serial.println (charData);
        
//        int bytesSent = MESH_SERIAL.write (charData);
//        Serial.print ("sent "); Serial.print (bytesSent); Serial.print (" bytes\n\n");
        
        lastBroadcastTime = millis ();
        
//        if (bytesSent >= data.length ()) {
//          isWriting = false;
//        }
//      }
    }
  }
  
  // TODO: Broadcast the foundation's default device address (upon boot)
  
  // TODO: Negotiate a unique dynamic mesh address
 
  // TODO: Broadcast the platform's dynamic mesh address (once per 30 seconds or so)
  
  Perform_Light_Behavior ();
  
  lastInputValue = touchInputMean;
  
  // Get module's input
  Get_Input_Port_Continuous ();  
  // Serial.println(touchInputMean); // Output value for debugging (or manual calibration)
  
  if (touchInputMean > 3000 && lastInputValue <= 3000) { // Check if state changed to "pressed" from "not pressed"
    if (outputPinRemote == false) {
      // Output port is on this module!
      //Update_Channel_Value (MODULE_OUTPUT_PIN, PIN_VALUE_HIGH);
      Channel* moduleOutputChannel = Get_Channel (platform, MODULE_OUTPUT_PIN);
      Update_Channel_Value (moduleOutputChannel, PIN_VALUE_HIGH);
      Propagate_Channel_Value (moduleOutputChannel);
      Blink_Light (1);
    } else {
      // Output port is on a different module than this one!
      Blink_Light (2);
      Queue_Message (BROADCAST_ADDRESS, ACTIVATE_MODULE_OUTPUT);
    }
//    delay(500);
  } else if (touchInputMean <= 3000 && lastInputValue > 3000) { // Check if state changed to "not pressed" from "pressed"
    if (outputPinRemote == false) {
//      Update_Channel_Value (MODULE_OUTPUT_PIN, PIN_VALUE_LOW);
//      syncPinValue(MODULE_OUTPUT_PIN);
      Channel* moduleOutputChannel = Get_Channel (platform, MODULE_OUTPUT_PIN);
      Update_Channel_Value (moduleOutputChannel, PIN_VALUE_LOW);
      Propagate_Channel_Value (moduleOutputChannel);
    } else {
      Queue_Message (BROADCAST_ADDRESS, DEACTIVATE_MODULE_OUTPUT);
    }
//    delay(500);
  }

  // TODO: Send updated state of THIS board (master) to the OTHER board (slave) for caching.
    
  // Get behavior updates from slave
  Get_Behavior_Transformations ();
  
  // Perform behavior step in the interpreter (Evaluate)
  // TODO: Transform_Behavior (i.e., the Behavior Transformer does this, akin to interpreting an instruction/command)
  boolean performanceResult = Perform_Behavior (performer);
  
  
  
  ////// GESTURE/MODULE STUFF (MASTER)
  
  // TODO: Add "getPins" function to read the state of pins, store the state of the pins, and handle interfacing with the pins (reading, writing), based on the program running (in both Looper and Mover).
  // TODO: Write code to allow Processing sketch (or other software) to automatically connect to this serial port. Send a "waiting for connection" signal one per second (or thereabout).
  
//  if (getPreviousModuleCount()) {
//    Serial.print("Previous modules: ");
//    Serial.print(getPreviousModuleCount());
//    Serial.println();
//  }
//  
//  if (getNextModuleCount()) {
//    Serial.print("Next modules: ");
//    Serial.print(getNextModuleCount());
//    Serial.println();
//  }

  // Change color/light if needed
  if (crossfadeStep < 256) {
    Light_Apply_Color ();
  }
  
  //
  // Get data from mesh network
  //
  
  unsigned long currentTime = millis ();
  
  // Update gesture/mesh communication timers
  // TODO: Add this to Looper's timers!
  if (lastSwingAddress != -1) {
    if (currentTime - lastReceivedSwingTime > lastReceivedSwingTimeout) {
      lastSwingAddress = -1;
    }
  }
  
  // Update gesture/mesh communication timers
  // TODO: Add this to Looper's timer!
  if (hasSwung == true) {
    currentTime = millis ();
    if (currentTime - lastSwingTime > lastSwingTimeout) {
      
      // Cancel swing gesture
      Stop_Blink_Light ();
      hasSwung = false;
      
      // Reset the timer
      lastSwingTime = 0L;
    }
  }
  
  // Broadcast message notifying other modules that this module is still active (i.e., broadcast this module's "heartbeat")
  currentTime = millis ();
  if (currentTime - lastSentActive >= lastSentActiveTimeout) {
    Queue_Broadcast (ANNOUNCE_ACTIVE);
    lastSentActive = millis ();
  }
  
  
  // Check for mesh data and receive it if present
  boolean hasReceivedMeshData = false;
  hasReceivedMeshData = Collect_Mesh_Messages ();
  
  //
  // Sense gesture (and phsyical orientation, generally)
  //
  
  boolean hasGestureChanged = false;
  if (senseOrientation ()) {
    storeData ();
    
    // Classify live gesture sample
    unsigned long currentTime = millis();
    if (currentTime - lastGestureClassificationTime >= gestureSustainDuration[classifiedGestureIndex]) { // Check if gesture duration has expired
      classifiedGestureIndex = classifyGestureFromTransitions(); // (gestureCandidate);
      
      if (classifyMostFrequentGesture) {
        // Add the most recent gesture classification to the end of the classification history list
        if (previousClassifiedGestureCount < PREVIOUS_CLASSIFIED_GESTURE_COUNT) {
          previousClassifiedGestures[previousClassifiedGestureCount] = classifiedGestureIndex;
          previousClassifiedGestureCount++;
        } else {
          for (int i = 0; i < (PREVIOUS_CLASSIFIED_GESTURE_COUNT - 1); i++) {
            previousClassifiedGestures[i] = previousClassifiedGestures[i + 1];
          }
          previousClassifiedGestures[PREVIOUS_CLASSIFIED_GESTURE_COUNT - 1] = classifiedGestureIndex;
        }
        
        // Get the most frequently classified gesture in the history
        for (int i = 0; i < GESTURE_COUNT; i++) { // Reset the previous classified gesture frequency (the number of times each occured in the short history)
          previousClassifiedGestureFrequency[i] = 0;
        }
        
        // Count the number of times each previous gesture occurred i.e., compute frequency of gesture classifications in short history)
        for (int i = 0; i < previousClassifiedGestureCount; i++) {
          int previouslyClassifiedGestureIndex = previousClassifiedGestures[i]; // Get a previous gesture's index
          previousClassifiedGestureFrequency[previouslyClassifiedGestureIndex]++; // Increment the gesture's frequency by one
        }
        
        // Determine the gesture most frequently classified
        int mostFrequentGestureIndex = 0;
        for (int i = 0; i < GESTURE_COUNT; i++) {
  //        Serial.print(previousClassifiedGestureFrequency[i]); Serial.print(" ");
          if (previousClassifiedGestureFrequency[i] > previousClassifiedGestureFrequency[mostFrequentGestureIndex]) {
            mostFrequentGestureIndex = i;
          }
        }
  //      Serial.println();
        
        // Update the classified gesture to the most frequent one
        classifiedGestureIndex = mostFrequentGestureIndex;
      }
      
      // HACK: Doesn't allow tilt left and tilt right (reclassifies them as "at rest, in hand"
//      if (classifiedGestureIndex == 4 || classifiedGestureIndex == 5) {
//        classifiedGestureIndex = 1;
//      }

      if (classifiedGestureIndex == 4) { // Ignore shake gesture if not yet swung
        // TODO: Check if has a "remote output", and if so, then DO NOT ignore the swing gesture.
        if (hasSwung == false) {
          if (outputPinRemote == true) {
//            classifiedGestureIndex = 4; // Set "shake" to "at rest"
          } else {
            classifiedGestureIndex = 1; // Change "shake" to "swing" (since they're similar enough for this to make sense)
          }
        }
      } else if (classifiedGestureIndex == 2 || classifiedGestureIndex == 3) { // If hasn't yet swung, then ignore tap gestures
        if (lastSwingAddress == -1) {
          classifiedGestureIndex = 0; // Set to "at rest"
        }
      } else if (classifiedGestureIndex == 1) { // If has swung, don't allow another swing if already swung (no effect)
        if (hasSwung) {
          classifiedGestureIndex = previousClassifiedGestureIndex;
        }
      }
      
      lastGestureClassificationTime = millis(); // Update time of most recent gesture classification
    }
    
    // Update current gesture (if it has changed)
    if (classifiedGestureIndex != previousClassifiedGestureIndex) {
      Serial.print("Detected gesture: ");
      Serial.print(gestureName[classifiedGestureIndex]);
      Serial.println();
      
      // Update the previous gesture to the current gesture
      previousClassifiedGestureIndex = classifiedGestureIndex;
      
      // Indicate that the gesture has changed
      hasGestureChanged = true;
      hasGestureProcessed = false;
      
      // TODO: Process newly classified gesture
      // TODO: Make sure the transition can happen (with respect to timing, "transition cooldown")
    }
  }
  
  //
  // Gesture Interpreter:
  // Process gestures. Perform the action associated with the gesture.
  //
  
  // Process current gesture (if it hasn't been processed yet)
  if (hasGestureChanged) { // Only executed when the gesture has changed
    if (!hasGestureProcessed) { // Only executed when the gesture hasn't yet been processed
      
      // Handle gesture
      if (classifiedGestureIndex == 0) { // Check if gesture is "at rest"
        Handle_Gesture_At_Rest ();
      } else if (classifiedGestureIndex == 1) { // Check if gesture is "swing"
        Handle_Gesture_Swing ();
      } else if (classifiedGestureIndex == 2) { // Check if gesture is "tap to another, as left"
        Handle_Gesture_Tap ();
        // Handle_Gesture_Tap_As_Left ();
      } else if (classifiedGestureIndex == 3) { // Check if gesture is "tap to another, as right"
        Handle_Gesture_Tap ();
        // Handle_Gesture_Tap_As_Right ();
      } else if (classifiedGestureIndex == 4) { // Check if gesture is "shake"
        Handle_Gesture_Shake ();
      } else if (classifiedGestureIndex == 5) { // Check if gesture is "tilt left"
        Handle_Gesture_Tilt_Left ();
      } else if (classifiedGestureIndex == 6) { // Check if gesture is "tilt right"
        Handle_Gesture_Tilt_Right ();
      } else if (classifiedGestureIndex == 7) { // Check if gesture is "tilt forward"
        Handle_Gesture_Tilt_Forward ();
      } else if (classifiedGestureIndex == 8) { // Check if gesture is "tilt backward"
        Handle_Gesture_Tilt_Backward ();
      }
      
      hasGestureProcessed = true; // Set flag indicating gesture has been processed
    }
  }
  
  //
  // Process incoming messages in queue (if any)
  //
  
  if (incomingMessageQueueSize > 0) {
    Message message = Dequeue_Incoming_Mesh_Message ();
    
    Serial.print ("Received ");
    
    // Sent by "left" module:
    if (message.message == ANNOUNCE_ACTIVE) {
      Serial.print ("ANNOUNCE_ACTIVE");
    }
    
    else if (message.message == ANNOUNCE_GESTURE_SWING) {
      Serial.print("ANNOUNCE_GESTURE_SWING");
    } else if (message.message == ANNOUNCE_GESTURE_TAP) {
      Serial.print("ANNOUNCE_GESTURE_TAP");
    }
    
    else if (message.message == ANNOUNCE_GESTURE_TAP_AS_LEFT) {
      Serial.print("ANNOUNCE_GESTURE_TAP_AS_LEFT");
    } else if (message.message == REQUEST_CONFIRM_GESTURE_TAP_AS_RIGHT) {
      Serial.print("REQUEST_CONFIRM_GESTURE_TAP_AS_RIGHT");
    } else if (message.message == CONFIRM_GESTURE_TAP_AS_LEFT) {
      Serial.print("CONFIRM_GESTURE_TAP_AS_LEFT");
    }
    
    // Sent by "right" module:
    else if (message.message == ANNOUNCE_GESTURE_TAP_AS_RIGHT) {
      Serial.print("ANNOUNCE_GESTURE_TAP_AS_RIGHT");
    } else if (message.message == REQUEST_CONFIRM_GESTURE_TAP_AS_LEFT) {
      Serial.print("REQUEST_CONFIRM_GESTURE_TAP_AS_LEFT");
    } else if (message.message == CONFIRM_GESTURE_TAP_AS_RIGHT) {
      Serial.print("CONFIRM_GESTURE_TAP_AS_RIGHT");
    }
    
    else if (message.message == ACTIVATE_MODULE_OUTPUT) {
      Serial.print("ACTIVATE_MODULE_OUTPUT");
    } else if (message.message == DEACTIVATE_MODULE_OUTPUT) {
      Serial.print("DEACTIVATE_MODULE_OUTPUT");
    }
    
    else {
      Serial.print(message.message);
    }
    
    Serial.print(" from module ");
    Serial.print(message.source);
    Serial.print(" (of ");
    Serial.print(incomingMessageQueueSize);
    Serial.print(")\n");
    
    //
    // Process received messages
    //

    if (message.message == ANNOUNCE_ACTIVE) {
      Handle_Message_Active (message);
    }
    
    else if (message.message == ANNOUNCE_GESTURE_SWING) {
      Handle_Message_Swing (message);
    } else if (message.message == ANNOUNCE_GESTURE_SHAKE) {
      Handle_Message_Shake (message);
    } else if (message.message == ANNOUNCE_GESTURE_TAP) { // From a module that just recognized a "tap" gesture.
      Handle_Message_Tap (message);
    } else if (message.message == REQUEST_CONFIRM_GESTURE_TAP) { // From a module that just recognized a "tap" gesture.
      Handle_Message_Request_Confirm_Tap (message);
    } else if (message.message == CONFIRM_GESTURE_TAP) { // From a module that just recognized a "tap" gesture.
      Handle_Message_Confirm_Tap (message);
    }
    
    else if (message.message == ANNOUNCE_GESTURE_TAP_AS_LEFT) { // From "left" module. "Left" module announces that it was tapped to another module as the left module [Sequence: Sequencing request (i.e., linking) confirmation, from "right" module]
      Handle_Message_Tap_To_Another_As_Left (message);
    } else if (message.message == REQUEST_CONFIRM_GESTURE_TAP_AS_LEFT) { // From "left" module. "Left" module requests "right" module to confirm that it received "ANNOUNCE_GESTURE_TAP_AS_LEFT"
       Handle_Message_Request_Confirm_Tap_To_Another_As_Left (message);
    } else if (message.message == CONFIRM_GESTURE_TAP_AS_LEFT) { // From "right" module (if it received the message from the "left" module). // Sequence: Sequencing (i.e., linking) confirmation, from "right" module
      Handle_Message_Confirm_Tap_To_Another_As_Left (message);
    } else if (message.message == ANNOUNCE_GESTURE_TAP_AS_RIGHT) { // From "right" module. // Sequence: Sequencing request (i.e., linking) confirmation, from "left" module
      Handle_Message_Tap_To_Another_As_Right (message);
    } else if (message.message == REQUEST_CONFIRM_GESTURE_TAP_AS_RIGHT) { // From "right" module. // Sequence: Sequencing (i.e., linking) confirmation, from "left" module
      Handle_Message_Request_Confirm_Tap_To_Another_As_Right (message);
    } else if (message.message == CONFIRM_GESTURE_TAP_AS_RIGHT) { // From "left" module (if it received the messsage from the "right" module). // Sequence: Sequencing (i.e., linking) confirmation, from "right" module
      Handle_Message_Confirm_Tap_To_Another_As_Right (message);
      // Serial.println(">> Receiving CONFIRM_GESTURE_TAP_AS_LEFT");
    
    } else if (message.message == ACTIVATE_MODULE_OUTPUT) {
      // ACTIVATE_MODULE_OUTPUT
//      Update_Channel_Value (MODULE_OUTPUT_PIN, PIN_VALUE_HIGH);
//      syncPinValue(MODULE_OUTPUT_PIN);
      Channel* moduleOutputChannel = Get_Channel (platform, MODULE_OUTPUT_PIN);
      Update_Channel_Value (moduleOutputChannel, PIN_VALUE_HIGH);
      Propagate_Channel_Value (moduleOutputChannel);
    } else if (message.message == DEACTIVATE_MODULE_OUTPUT) {
//      Update_Channel_Value (MODULE_OUTPUT_PIN, PIN_VALUE_LOW);
//      syncPinValue(MODULE_OUTPUT_PIN);
      Channel* moduleOutputChannel = Get_Channel (platform, MODULE_OUTPUT_PIN);
      Update_Channel_Value (moduleOutputChannel, PIN_VALUE_LOW);
      Propagate_Channel_Value (moduleOutputChannel);
    }
  }
  
  //
  // Update state of current module
  //
  
  //if (awaitingNextModuleConfirm) {
  if (awaitingNextModule) {
    unsigned long currentTime = millis ();
    if (currentTime - awaitingNextModuleStartTime > SEQUENCE_REQUEST_TIMEOUT) {
      Serial.println ("awaitingNextModule reset");
      awaitingNextModule = false;
      awaitingNextModuleConfirm = false;
    }
  }
  
  //if (awaitingPreviousModuleConfirm) {
  if (awaitingPreviousModule) {
    unsigned long currentTime = millis ();
    if (currentTime - awaitingPreviousModuleStartTime > SEQUENCE_REQUEST_TIMEOUT) {
      Serial.println ("awaitingPreviousModule reset");
      awaitingPreviousModule = false;
      awaitingPreviousModuleConfirm = false;
    }
  }
  
  //
  // Send outgoing messages (e.g., this module's updated gesture)
  //
  
  currentTime = millis();
  if (currentTime - lastMessageSendTime > PACKET_WRITE_TIMEOUT) {
  
    // Process mesh message queue  
    if (messageQueueSize > 0) {
      Send_Message ();
    }
    
    // Update the time that a message was most-recently dispatched
    lastMessageSendTime = millis();
  }
}
