/*
"Pixel" Firmware, Rendition 2
Michael Gubbels
*/

#include <Wire.h>
#include <SoftwareSerial.h>
#include <RadioBlock.h>
#include <SPI.h>

#include "Light.h"
#include "Gesture.h"
#include "Movement.h"
#include "Communication.h"

#define DEVICE_ADDRESS   0x0001

//#if defined(DEVICE_ADDRESS)
#if DEVICE_ADDRESS == 0x0001
  #define NEIGHBOR_ADDRESS 0x0002
#elif DEVICE_ADDRESS == 0x0002
  #define NEIGHBOR_ADDRESS 0x0001
#endif

#define BROADCAST_ADDRESS NEIGHBOR_ADDRESS // 0xFFFF

// Mesh outgoing message queue
#define MESSAGE_QUEUE_CAPACITY 20
Message messageQueue[MESSAGE_QUEUE_CAPACITY];
int messageQueueSize = 0;

/**
 * RadioBlocks Setup
 */

#define RADIOBLOCK_PACKET_READ_TIMEOUT 40 // 100
#define PAYLOAD_START_INDEX 5 // Index of the first byte in the payload
#define RADIOBLOCK_PACKET_WRITE_TIMEOUT 120 // 200

// The module's pins 1, 2, 3, and 4 are connected to pins 5V, GND, 8, and 7.
RadioBlockSerialInterface interface = RadioBlockSerialInterface(-1, -1, 8, 7);

/**
 * Device Setup
 */

boolean hasCounter = false;
unsigned long lastCount = 0;
#define NEIGHBOR_COUNT 2
unsigned short int neighbors[NEIGHBOR_COUNT];
unsigned short int next[1];

//            _               
//           | |              
//   ___  ___| |_ _   _ _ __  
//  / __|/ _ \ __| | | | '_ \ 
//  \__ \  __/ |_| |_| | |_) |
//  |___/\___|\__|\__,_| .__/ 
//                     | |    
//                     |_|    

void setup() {
  
  color[0] = 205;
  color[1] = 205;
  color[2] = 205;
  
  for (int i = 0; i < 20; i++) {
    color[0] = random(256);
    color[1] = random(256);
    color[2] = random(256);
    setColor(color[0], color[1], color[2]);
    ledOn();
    delay(50);
  }
  ledOff();
  
  ledOn();
  delay(100);
  ledOff();
  delay(100);
  ledOn();
  delay(100);
  ledOff();
  delay(100);
  ledOn();
  delay(100);
  ledOff();
//  fadeOn();
//  fadeOff();
  
  randomSeed(analogRead(0));
  
  // Setup mesh networking peripherals (i.e., RadioBlocks)
  setupMesh();
  
  //
  // Setup serial communication (for debugging)
  //
  
  Serial.begin(9600);
  Serial.println(F("Pixel 2014.03.29.17.38.01"));
  
  // Setup IMU peripherals
  setupIMU();
  
  // Assign the module a unique color
//  color[0] = random(256);
//  color[1] = random(256);
//  color[2] = random(256);
  color[0] = 255;
  color[1] = 255;
  color[2] = 0;
  setColor(color[0], color[1], color[2]);
  
  // Flash RGB LEDs
  // setColor(255, 255, 255);
  ledOn();
  delay(100);
  ledOff();
  delay(100);
  ledOn();
  delay(100);
  ledOff();
  delay(100);
  ledOn();
  delay(100);
  ledOff();
}

/**
 * Initialize mesh networking peripheral.
 */
boolean setupMesh() {
  
//  delay(1000);
  
  interface.begin();
  
  // Give RadioBlock time to init
  delay(500);
  
  // Flash the LED a few times to tell that the module is live
  interface.setLED(true);
  delay(200);
  interface.setLED(false);
  delay(200);
  interface.setLED(true);
  delay(200);
  interface.setLED(false);
  delay(200);
  interface.setLED(true);
  delay(200);
  interface.setLED(false);
  
  interface.setChannel(15);
  interface.setPanID(0xBAAD);
  interface.setAddress(DEVICE_ADDRESS);
}

/**
 * Initialize the IMU peripheral (inertial measurement unit).
 */
boolean setupIMU() {

  Serial.println("Initializing IMU...");
  I2C_Init();

  delay(1500);

  Accel_Init();
  Compass_Init();
  Gyro_Init();
  Alt_Init();

  delay(20); // Wait for a small duration for the IMU sensors to initialize (?)

  for (int i = 0;i < 32; i++) { // We take some initial readings... (to warm the IMU up?)
    Read_Gyro();
    Read_Accel();
    for (int y = 0; y < 6; y++) { // Cumulate values
        AN_OFFSET[y] += AN[y];
    }
    delay(20);
  }

  for (int y = 0; y < 6; y++) {
    AN_OFFSET[y] = AN_OFFSET[y]/32;
  }

  AN_OFFSET[5] -= GRAVITY * SENSOR_SIGN[5];

  Serial.println("Offset:");
  for (int y = 0; y < 6; y++) {
    Serial.println(AN_OFFSET[y]);
  }

  delay(1000);

  timer = millis();
  delay(20);
  counter = 0;
}

//   _                   
//  | |                  
//  | | ___   ___  _ __  
//  | |/ _ \ / _ \| '_ \ 
//  | | (_) | (_) | |_) |
//  |_|\___/ \___/| .__/ 
//                | |    
//                |_|    

boolean awaitingNextModule = false;
boolean awaitingPreviousModule = false;
boolean awaitingNextModuleConfirm = false;
unsigned long awaitingNextModuleStartTime = 0;
unsigned long awaitingPreviousModuleStartTime = 0;

boolean hasGestureProcessed = false;

void loop() {
  
//  // List size
//  Serial.print("previousModuleCount = ");
//  Serial.print(previousModuleCount);
//  Serial.print("\n");
//  
//  // Print list
//  Serial.print("List: ");
//  for (int i = 0; i < previousModuleCount; i++) {
//    Serial.print(previousModules[i]);
//    Serial.print(" ");
//  }
//  Serial.print("\n");
//  
//  addPreviousModule(3);
//  addPreviousModule(3);
//  addPreviousModule(4);
//  // List size
//  Serial.print("previousModuleCount = ");
//  Serial.print(previousModuleCount);
//  Serial.print("\n");
//  
//  // Print list
//  Serial.print("List: ");
//  for (int i = 0; i < previousModuleCount; i++) {
//    Serial.print(previousModules[i]);
//    Serial.print(" ");
//  }
//  Serial.print("\n");
//  
//  removePreviousModule(3);
//  // List size
//  Serial.print("previousModuleCount = ");
//  Serial.print(previousModuleCount);
//  Serial.print("\n");
//  
//  Serial.println(removePreviousModule(5));
//  
//  Serial.println(hasPreviousModule(5));
//  Serial.println(hasPreviousModule(4));
//  Serial.println(hasPreviousModule(3));
//  
//  return;
  
  // Get data from mesh network
  boolean hasReceivedMeshData = false;
  hasReceivedMeshData = receiveMeshData();
  
//  for(int gesture = 0; gesture < GESTURE_COUNT; gesture++) {  
//    for(int axis = 0; axis < AXIS_COUNT; axis++) {
//      for(int point = 0; point < GESTURE_SIGNATURE_SIZE; point++) {
//        Serial.print(gestureSignature[gesture][axis][point]);
//        Serial.print(" ");
//      }
//      Serial.println();
//    }
//    Serial.println();
//  }
//  Serial.println();
  
  // TODO: Write code to allow Processing sketch (or other software) to automatically connect to this serial port. Send a "waiting for connection" signal.
  
  // Sense phsyical orientation data
  boolean hasGestureChanged = false;
  if (sensePhysicalData()) {
    storeData();
    
    // Classify live gesture sample
    unsigned long currentTime = millis();
    if (currentTime - lastGestureClassificationTime >= gestureSustainDuration[classifiedGestureIndex]) { // Check if gesture duration has expired
      classifiedGestureIndex = classifyGestureFromTransitions(); // (gestureCandidate);
      
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
  // Gesture Interpreter
  //
  
  // Process current gesture (if it hasn't been processed yet)
  if (hasGestureChanged) { // Only executed when the gesture has changed
    if (!hasGestureProcessed) { // Only executed when the gesture hasn't yet been processed
      
      // Handle gesture
      if (classifiedGestureIndex == 0) { // Check if gesture is "at rest, on table"
        handleGestureAtRestOnTable();
      } else if (classifiedGestureIndex == 1) { // Check if gesture is "at rest, in hand"
        handleGestureAtRestInHand();
      } else if (classifiedGestureIndex == 2) { // Check if gesture is "pick up"
        handleGesturePickUp();
      } else if (classifiedGestureIndex == 3) { // Check if gesture is "place down"
        handleGesturePlaceDown();
      } else if (classifiedGestureIndex == 4) { // Check if gesture is "tilt left"
        handleGestureTiltLeft();
      } else if (classifiedGestureIndex == 5) { // Check if gesture is "tilt right"
        handleGestureTiltRight();
      } else if (classifiedGestureIndex == 6) { // Check if gesture is "shake"
        handleGestureShake();
      } else if (classifiedGestureIndex == 7) { // Check if gesture is "tap to another, as left"
        handleGestureTapToAnotherAsLeft();    
      } else if (classifiedGestureIndex == 8) { // Check if gesture is "tap to another, as right"
        handleGestureTapToAnotherAsRight();
      }
      
      hasGestureProcessed = true; // Set flag indicating gesture has been processed
    }
  }
  
  //
  // Receive and process incoming messages
  //
  
  if (meshIncomingMessageQueueSize > 0) {
    Message message = dequeueIncomingMeshMessage();
    
    Serial.print("Received ");
//    Serial.print(gestureName[message.message]);
    Serial.print(message.message);
    Serial.print(" from module ");
    Serial.print(message.source);
    Serial.print(" (of ");
    Serial.print(meshIncomingMessageQueueSize);
    Serial.print(")\n");
    
    //
    // Process incoming message
    //
    
    if (message.message == 8) {
      // If receive "tap to another, as left", then check if this module performed "tap to another, as right" recently. If so, link the modules in a sequence, starting with the other module first.
      
      if (awaitingPreviousModule) {
        // TODO: previous += [ message.source ]
        
        awaitingPreviousModule = false;
        awaitingNextModuleConfirm = true;
        
        // Send ACK message to message.source to confirm linking operation
        //addMessage(message.source, 13);
        addBroadcast(13);
        
        // TODO: Wait for ACK response before the following... move it in another ACK message event handler.
        
        addPreviousModule(message.source);
        
        setColor(255, 255, 255);
        ledOn();
        delay(60);
        ledOff();
        delay(60);
        ledOn();
        delay(60);
        ledOff();
        delay(60);
        ledOn();
        delay(1500);
      }
      
    } else if (message.message == 9) {
      // If receive "tap to another, as right", then check if this module performed "tap to another, as left" recently. If so, link the modules in a sequence, starting with this module first.
      
      if (awaitingNextModule) {
        // TODO: next += [ message.source ]
        // Send "linked" to module (handshake)
        // TODO: In other module (and this one), when awaitingNextModule is true, look through the received messages for message "9"
        
        awaitingNextModule = false;
        awaitingNextModuleConfirm = true;
        
        // Send ACK message to message.source to confirm linking operation
//        addMessage(message.source, 13);
        addBroadcast(13);
        
        // TODO: Wait for ACK response before the following... move it in another ACK message event handler.
        
        addNextModule(message.source);
        
        setColor(255, 255, 255);
        ledOn();
        delay(60);
        ledOff();
        delay(60);
        ledOn();
        delay(60);
        ledOff();
        delay(60);
        ledOn();
        delay(1500);
      }
      
    } else if (message.message == 13) { // Sequence confirmation
    
      Serial.println(">>>> PROCESSING MESSAGE 13");
      
//      if (awaitingNextModule) {
        
        // awaitingNextModule = false;
        // awaitingNextModuleConfirm = true;
        
        // Send ACK message to message.source to confirm linking operation (if not yet done)
        if (awaitingNextModuleConfirm) {
//          addMessage(message.source, 13);
          addBroadcast(13);
//        addMessage(message.source, 14);

          awaitingNextModuleConfirm = false;
        }
        
        setColor(255, 255, 255);
        ledOn();
        delay(200);
        ledOff();
        delay(200);
        ledOn();
        delay(200);
        ledOff();
        delay(200);
        ledOn();
        
        // TODO: Wait for ACK response before the following... move it in another ACK message event handler.
        
        //addNextModule(message.source);
//      }
    }
  }
  
  //
  // Send message with updated gesture
  //
  
  // TODO: Handle "ongoing" gesture (i.e., do the stuff that should be done more than once, or as long as the gesture is active)
  
  // Process mesh message queue  
  if (messageQueueSize > 0) {
    sendMessage();
  }
    
  unsigned long currentTime = millis();
  if (currentTime - lastCount > RADIOBLOCK_PACKET_WRITE_TIMEOUT) {
  
    // Process mesh message queue  
//    if (messageQueueSize > 0) {
//      sendMessage();
//    }
    
    // Update the time that a message was most-recently dispatched
    lastCount = millis();
  }
}

/**
 * Read the IMU sensor data and estimate the module's orientation. Orientation is 
 * estimated using the DCM (Direction Cosine Matrix).
 */
boolean sensePhysicalData() {
  
  if ((millis() - timer) >= 20) { // Main loop runs at 50Hz
    counter++;
    timer_old = timer;
    timer = millis();
    if (timer > timer_old) {
      G_Dt = (timer-timer_old) / 1000.0; // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
    } else {
      G_Dt = 0;
    }

    // DCM algorithm:

    // Data adquisition
    Read_Gyro(); // This read gyro data
    Read_Accel(); // Read I2C accelerometer

    if (counter > 5) { // Read compass data at 10 Hz... (5 loop runs)
      counter = 0;
      Read_Compass(); // Read I2C magnetometer
      Compass_Heading(); // Calculate magnetic heading
    }

    // Read pressure/altimeter
    Read_Altimeter();

    // Calculations...
    Matrix_update(); 
    Normalize();
    Drift_correction();
    Euler_angles();
    
    return true;
  } else {
    return false;
  }
}

/**
 * Handle "at rest, on table" gesture.
 */
boolean handleGestureAtRestOnTable() {
  //crossfadeColor(0, 0, 0);
  ledOff();
  
  addBroadcast(1);
}

/**
 * Handle "at rest, in hand" gesture.
 */
boolean handleGestureAtRestInHand() {
  addBroadcast(2);
  
//  crossfadeColor(color[0], color[1], color[2]);
  setColor(color[0], color[1], color[2]);
  ledOn();
  
//  crossfadeColor(255, 0, 0);
//  crossfadeColor(0, 255, 0);
//  crossfadeColor(0, 0, 255);
//  crossfadeColor(255, 255, 0);
//  crossfadeColor(0, 255, 255);
//  crossfadeColor(255, 255, 255);
}

/**
 * Handle "pick up" gesture.
 */
boolean handleGesturePickUp() {
  addBroadcast(3);
}

/**
 * Handle "place down" gesture.
 */
boolean handleGesturePlaceDown() {
  addBroadcast(4);
}

/**
 * Handle "tilt left" gesture.
 */
boolean handleGestureTiltLeft() {
  addBroadcast(5);
  
  crossfadeColor(0, 0, 255);
}

/**
 * Handle "tilt right" gesture.
 */
boolean handleGestureTiltRight() {
  addBroadcast(6);
  
  crossfadeColor(0, 255, 0);
}

/**
 * Handle "shake" gesture.
 */
boolean handleGestureShake() {
  addBroadcast(7);
  
  setColor(255, 0, 0);
  ledOn();
}

/**
 * Handle "tap to another, as left" gesture.
 */
boolean handleGestureTapToAnotherAsLeft() {
  addBroadcast(8);
  awaitingNextModule = true;
  awaitingNextModuleStartTime = millis();
  
  color[0] = 255;
  color[1] = 0;
  color[2] = 0;
}

/**
 * Handle "tap to another, as right" gesture.
 */
boolean handleGestureTapToAnotherAsRight() {
  addBroadcast(9);
  awaitingPreviousModule = true;
  awaitingPreviousModuleStartTime = millis();

  color[0] = 0;
  color[1] = 0;
  color[2] = 255;
  
  // Send to all linked devices
//      for (int i = 0; i < 1; i++) {
//          // Set the destination address
//          interface.setupMessage(next[i]);
//  
//          // Package the data payload for transmission
//          interface.addData(1, (byte) 0x1F); // TYPE_INT8
//          interface.sendMessage(); // Send data OTA
//  
//          // Wait for confirmation
//          // delayUntilConfirmation();
//      }
}

/**
 * Push a message onto the queue of messages to be processed and sent via the mesh network.
 */
boolean addBroadcast(int message) {
  if (messageQueueSize < MESSAGE_QUEUE_CAPACITY) { // Check if message queue is full (if so, don't add the message)
    //messageQueue[messageQueueSize] = message; // Add message to the back of the queue
    messageQueue[messageQueueSize].source = BROADCAST_ADDRESS; // Set "broadcast address"
    messageQueue[messageQueueSize].message = message; // Add message to the back of the queue
    messageQueueSize++; // Increment the message count
  }
}

/**
 * Push a message onto the queue of messages to be processed and sent via the mesh network.
 */
boolean addMessage(int source, int message) {
  if (messageQueueSize < MESSAGE_QUEUE_CAPACITY) { // Check if message queue is full (if so, don't add the message)  
    //messageQueue[messageQueueSize] = message; // Add message to the back of the queue
    messageQueue[messageQueueSize].source = source;
    messageQueue[messageQueueSize].message = message; // Add message to the back of the queue
    messageQueueSize++; // Increment the message count
  }
}

Message dequeueOutgoingMessage() {
  
  if (messageQueueSize > 0) {
    
    // Get the next message from the front of the queue
    //unsigned short int message = meshIncomingMessages[0].message; // Get message on front of queue
    Message message = { messageQueue[0].source, messageQueue[0].message }; // Get message on front of queue
    messageQueueSize--;
    
    // Shift the remaining messages forward one position in the queue
    for (int i = 0; i < MESSAGE_QUEUE_CAPACITY - 1; i++) {
      messageQueue[i].source = messageQueue[i + 1].source;
      messageQueue[i].message = messageQueue[i + 1].message;
    }
    messageQueue[MESSAGE_QUEUE_CAPACITY - 1].source = -1; // Set last message to "noop"
    messageQueue[MESSAGE_QUEUE_CAPACITY - 1].message = -1; // Set last message to "noop"
    
    return message;
  }
}

/**
 * Sends the top message on the mesh's message queue.
 */
boolean sendMessage() {
  if (messageQueueSize > 0) {
    
    // Get the next message from the front of the queue
//    unsigned short int message = messageQueue[0]; // Get message on front of queue
//    messageQueueSize--;
    Message message = dequeueOutgoingMessage();
    
//    // Shift the remaining messages forward one position in the queue
//    for (int i = 0; i < MESSAGE_QUEUE_CAPACITY - 1; i++) {
//      messageQueue[i] = messageQueue[i + 1];
//    }
//    messageQueue[MESSAGE_QUEUE_CAPACITY - 1] = 0; // Set last message to "noop"
    
    
    
    
    //
    // Actually send the message
    //
    
    // Set up the destination address of the message
    if (message.source == BROADCAST_ADDRESS) {
      // TODO: Broadcast here, not just send ot "neighbor"... might need to iterat through the addresses manually!
      interface.setupMessage(NEIGHBOR_ADDRESS);
    } else {
      interface.setupMessage(message.source); // Set the address of the recipient
    }
    
    Serial.print("Sending message: ");
    Serial.print(message.message);
    Serial.print(" to ");
    Serial.print(message.source);
    Serial.print("\n");
            
    // Package the data payload for transmission
    interface.addData(1, (unsigned char) message.message); // TYPE_UINT8

    // e.g., How to assemble data packets for sending with RadioBlocks
    // interface.addData(1, (unsigned char) 0x13); // TYPE_UINT8
    // interface.addData(1, (char) 0x14); // TYPE_INT8
    // interface.addData(3, (unsigned short int) 0xFFFD); // TYPE_UINT16
    // interface.addData(1, (short) 0xABCD); // TYPE_INT16
    // interface.addData(14, (unsigned long) 0xDDDDCCAA); // TYPE_UINT32
    // interface.addData(9, (long) 0xFF03CCAA); // TYPE_INT32
     
    // Send data OTA (over the air)
    interface.sendMessage();
  }
}

/**
 * Read received (and buffered) data from the RadioBlock.
 */
boolean receiveMeshData() {

  // if (interface.readPacket(RADIOBLOCK_PACKET_READ_TIMEOUT)) { // Waits a maximum of <i>timeout</i> milliseconds for a response packet before timing out; returns true if packet is read. Returns false if timeout or error occurs.
  interface.readPacket(); // Read the packet (NOTE: Seemingly must do this for isAvailable() to work properly.)
  if (interface.getResponse().isAvailable()) {
    // TODO: Change this to interface.isAvailable() so it doesn't block and wait for any time, so it just reads "when available" (in quotes because it's doing polling)
    
    // General command format (sizes are in bytes), Page 4:
    //
    // [ Start Byte (1) | Size (1) | Payload (Variable) | CRC (2) ]
    //
    // - Start Byte (1 byte)
    // - Size (1 byte): Size of the command id + options + payload field
    // - Payload (Variable): command payload
    // - CRC (2 bytes): 16 bit CRC calculated over payload with initial value 0x1234 (i.e., it is 
    //                  calculated over the command id, options, and payload if any.)
    
    // Data request command format (this is the Payload field in the command format):
    // 
    // [ Command ID (1) | Destination (2) | Options (1) | Handle (1) ]
    //
    // NOTE: I believe this constitutes a "frame".
    
    // Data response command format (this is the Payload field in the command format):
    // 
    // [ Command ID (1) | Source Address (2) | Options (1) | LQI (1) | RSSI (1) | Payload (Variable) ]
    //
    // NOTE: I believe this constitutes a "frame".
  
    if (interface.getResponse().getErrorCode() == APP_STATUS_SUCESS) {
      // Serial.println("\n\n\n\nReceived packet.");
      
      int commandId = interface.getResponse().getCommandId();
      
      if (commandId == APP_COMMAND_ACK) {
        // "Every command is confirmed with an acknowledgment command even if it is impossible
        //   to immediately execute the command. There is no particular order in which responses 
        //   are sent, so for example Data Indication Command might be sent before 
        //   Acknowledgment Command."
  
        // Acknowledgment command format: Page 5 of SimpleMesh Serial Protocol document.
  
        // Serial.println("Received Ack");
        // Serial.print("  Status: ");
        // Serial.println(interface.getResponse().getFrameData()[0], HEX); // Source address

      } else if (commandId == APP_COMMAND_DATA_IND) { // (i.e., 0x22) [Page 15]
      
//        // Queue incoming message!
//        queueIncomingMeshMessage(0, 8);
  
//        Serial.print(interface.getResponse().getFrameData()[0], HEX); // Frame options
//        Serial.print(" | ");
//        Serial.print(interface.getResponse().getFrameData()[1], HEX); // Frame options
//        Serial.print(" | ");
//        Serial.print(interface.getResponse().getFrameData()[2], HEX); // Frame options
//        Serial.print(" | ");
//        Serial.print(interface.getResponse().getFrameData()[3], HEX); // Frame options
//        Serial.print(" | ");
//        Serial.print(interface.getResponse().getFrameData()[4], HEX); // Frame options

        int frameDataLength = interface.getResponse().getFrameDataLength();
        //        Serial.print("  Payload length: ");
        //        Serial.println(frameDataLength, DEC); // "Payload" length (minus "Command Id" (1 byte))

        //        Serial.print("  Frame Command Id: ");
        //        Serial.println(interface.getResponse().getFrameData()[0], HEX); // Frame options

        // Compute source address using bitwise operators (combine two bytes into a "short", a 16-bit integer data type)
        short sourceAddress = interface.getResponse().getFrameData()[0] | ((short) interface.getResponse().getFrameData()[1] << 8);
//        Serial.print("  Source address: ");
//        Serial.println(sourceAddress, HEX); // Source address

        // Frame Options [Page 15]
        // i.e.,
        // 0x00 None
        // 0x01 Acknowledgment was requested
        // 0x02 Security was used
        //        Serial.print("  Frame options: ");
        //        Serial.println(interface.getResponse().getFrameData()[2], HEX); // Frame options
        //  
        //        Serial.print("  Link Quality Indicator: ");
        //        Serial.println(interface.getResponse().getFrameData()[3], HEX); // Link quality indicator
        //  
        //        Serial.print("  Received Signal Strength Indicator: ");
        //        Serial.println(interface.getResponse().getFrameData()[4], HEX); // Received Signal Strength Indicator

        // NOTE: Payload starts at index position 5

        //
        // Parse payload data
        //

        //        int PAYLOAD_START_INDEX = 5; // Index of first byte of "Payload"

        //        Serial.print("Raw Payload Data: [ ");
        //        for (int i = 0; i < (frameDataLength - PAYLOAD_START_INDEX - 1); i++) {
        //          Serial.print(interface.getResponse().getFrameData()[5 + i] , HEX);
        //          Serial.print(" : ");
        //        }
        //        Serial.print(interface.getResponse().getFrameData()[5 + (frameDataLength - PAYLOAD_START_INDEX - 1)], HEX);
        //        Serial.println(" ]");
        //        
        //        Serial.println("Parsed Payload Data:");

        // Get the method the sending unit used to construct the packet
        int sendMethod = -1;
        if (frameDataLength == 6) {
            sendMethod = 0; // The sender used sendData(). More data is expected to come along...
        } else if (frameDataLength > 6) {
            sendMethod = 1; // The sender used setupMessage(), addData(), and sendMessage()
        }

        // Parse payload data based on whether sendData() or the three functions setupMessage(), 
        // addData(), and sendMessage() were used.

        if (sendMethod != -1) { // Check if sendMethod is valid... if < 6, no data was attached...

            // "sendData()" was used, so only one byte of data was sent (since this function sends only one byte).
            // Therefore, extract the one byte of data from the first byte of the "Payload". [Page 15]
            if (sendMethod == 0) {

              Serial.print("  Sent Data: ");
              Serial.println(interface.getResponse().getFrameData()[5], HEX);

            } 
            else if (sendMethod == 1) {

                // The "Payload" field is packed in pairs, each pair consisting of a 1 byte code followed by a 
                // variable number of bytes of data, determinable by the 1 byte code.

                unsigned int codeAndType = 0;
                unsigned int payloadCode = 0;
                unsigned int payloadDataType = 0;

                int payloadOffset = 0;

                int loopCount = 0;
                int maxLoopCount = 20;

                while(payloadOffset < (frameDataLength - PAYLOAD_START_INDEX)) {

                    // Protect against infinite loop with this conditional
//                              if (loopCount > maxLoopCount) {
//                                  Serial.println("WARNING: loopCount > maxLoopCount");
//                                  interface.getResponse().reset(); // TODO: Possibly remove this. This might be a bad idea.
//                                  clearCounter();
//                                  return false;
//                                  break;
//                              }

                    codeAndType = interface.getResponse().getFrameData()[PAYLOAD_START_INDEX + payloadOffset];
                    //              Serial.print(" Encoded send code and original data type: ");
                    //              Serial.println(codeAndType, HEX); // The actual data

                    payloadDataType = codeAndType & 0xF;
                    payloadCode = (codeAndType >> 4) & 0xF;
                    //              Serial.print("  The sent code was (in hex): ");
                    //              Serial.println(payloadCode, HEX);
                    //              Serial.print("  The original data type was: ");
                    //              Serial.println(payloadDataType);

                    //
                    // Extract and type cast the data based on data type
                    //

                    if (payloadDataType == TYPE_UINT8) {

//                        Serial.println("   Data type is TYPE_UINT8. High and low bytes:");
//                        Serial.print("    High part: ");
//                        Serial.println(interface.getResponse().getFrameData()[PAYLOAD_START_INDEX + payloadOffset + 1]);

                        // Append message to message queue
//                        messageQueue = interface.getResponse().getFrameData()[PAYLOAD_START_INDEX + payloadOffset + 1];
                        int newMessage = interface.getResponse().getFrameData()[PAYLOAD_START_INDEX + payloadOffset + 1];

                        // Queue incoming message!
                        queueIncomingMeshMessage(sourceAddress, newMessage);

                        payloadOffset = payloadOffset + sizeof(unsigned char) + 1;

                    } else if (payloadDataType == TYPE_INT8) {

                        Serial.println("   Data type is TYPE_INT8. High and low bytes:");
                        Serial.print("    High part: ");
                        Serial.println(interface.getResponse().getFrameData()[PAYLOAD_START_INDEX + payloadOffset + 1]);

                        payloadOffset = payloadOffset + sizeof(char) + 1;

                    }

                    /* 
                     else if (payloadDataType == TYPE_UINT16) {
                     
                     Serial.println("   Data type is TYPE_UINT16. High and low bytes:");
                     Serial.print("    High part: ");
                     Serial.println(interface.getResponse().getFrameData()[PAYLOAD_START_INDEX + payloadOffset + 1]); 
                     Serial.print("    Low part: ");
                     Serial.println(interface.getResponse().getFrameData()[PAYLOAD_START_INDEX + payloadOffset + 2]);
                     
                     short unsigned int data = interface.getResponse().getFrameData()[PAYLOAD_START_INDEX + payloadOffset + 1] << 8 | ((unsigned short int) interface.getResponse().getFrameData()[PAYLOAD_START_INDEX + payloadOffset + 2]);
                     Serial.print("    Value: ");
                     Serial.println(data);
                     }
                     */

                    loopCount++;

                } // while()

                //
                // Process received data, update state
                //

                // Turn on if received counter
                //            setCounter();

            }
        } 
        
        // Return true if a packet was read (i.e., received) successfully
        // TODO: Add "return true" and "return false" cases to different conditions above, in this block.
        // return true;
        
        } else if (commandId == APP_COMMAND_DATA_CONF) {
        
//          Serial.println("APP_COMMAND_DATA_CONF");
          
          // return false; // Return true if a packet was read (i.e., received) successfully
        
        } else if (commandId == APP_COMMAND_GET_ADDR_RESP) { // (i.e., 0x25) [Page 15]
        
          Serial.print("  Frame Command Id: ");
          Serial.println(interface.getResponse().getFrameData()[0], HEX); // Frame options
  
          // Computer source address using bitwise operators (combine two bytes into a "short", a 16-bit integer data type)
//          address = interface.getResponse().getFrameData()[0] | ((short) interface.getResponse().getFrameData()[1] << 8);
//          Serial.print("  Device address: ");
//          Serial.println(address, HEX); // Source address
//
//          hasValidAddress = true;
  
          return false; // Return true if a packet was read (i.e., received) successfully
        }
  
      } else {
  
        Serial.println("Error: Failed to receive packet.");
        // TODO: Clear the buffer, check if this is causing messages to stop sending back and forth.
        // TODO: Reset!!
        
        // interface.getResponse().reset(); // TODO: Possibly remove this. This might be a bad idea.
        // clearCounter();
        return false; // Return true if a packet was read (i.e., received) successfully
      }
  
      // return true; // Return true if a packet was read (i.e., received) successfully
  
  } else if (interface.getResponse().isError()) { 
    
    int errorCode = interface.getResponse().getErrorCode();
    
    Serial.print("ERROR! (Code ");
    //  APP_STATUS_SUCESS               = 0x00, // Success
    //  // Unknown error
    //  // Out Of Memory
    //  // No Acknowledgment Was Received
    //  // Channel Access Failure
    //  // No Physical Acknowledgment Was Received
    //  APP_STATUS_INVALID_SIZE         = 0x80, // Invalid Command Size
    //  APP_STATUS_INVALID_CRC          = 0x81, // Invalid CRC
    //  APP_STATUS_TIMEOUT              = 0x82, // Timeout
    //  APP_STATUS_UNKNOWN_COMMAND      = 0x83, // Unknown Command
    //  APP_STATUS_MALFORMED_COMMAND    = 0x84, // Malformed Command
    //  APP_STATUS_FLASH_ERROR          = 0x85, // Internal Flash Error
    //  APP_STATUS_INVALID_PAYLOAD_SIZE = 0x86, // Invalid Data Request Payload Size
    Serial.print(errorCode);
    Serial.print(")\n");
    return false;
    
  } else { // Timeout or error occurred
  
    //Serial.println("UNKNOWN ERROR!");
//    return true; // TODO: Add a third state other than true or false
    return false;

  }
}
