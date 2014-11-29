#ifndef LANGUAGE_H
#define LANGUAGE_H

// TODO: Consider renaming "Interpret" to "Transducer" to remove the anthropomorphic feel of the word interpret. Or keep it for the same reason :). Just make the system aesthetic consistent.
void Interpret_Message (Message* message); // start the "interpretive dance": transformation/message => interpret => behavior
void Perform_Shell_Behavior (String consoleMessage);

String previousConsoleInput = "";
char consoleBuffer[64] = { 0 };
int consoleBufferSize = 0;

/**
 * This is the basic shell for the device.
 */
void Get_Console () { // TODO: Capture_Serial_Channel
  
//  terminalBufferSize = 0;

  // Read data on serial terminal (if any)
  while (Serial.available () > 0) {

    int incomingByte = Serial.read (); // receive a byte as character
    char c = (char) incomingByte;
    
    if (c == '\n') {
      consoleBuffer[consoleBufferSize] = '\0'; // Terminate console message buffer
      
      // Create a String from the terminal buffer
      String consoleMessage = String (consoleBuffer);
      
      if (consoleMessage.length () == 0) {
        consoleMessage = previousConsoleInput;
      } else {
        
        previousConsoleInput = consoleMessage;
        
//        // TODO: Don't separate "shell" behavior from other behaviors!
//        Perform_Shell_Behavior (consoleMessage);
        Message* message = Create_Message (platformUuid, perspectiveAddress, consoleMessage);
        Interpret_Message (message);
        
        consoleBufferSize = 0;
      }
      
      break;
    }
    
    // Copy byte into message buffer
    consoleBuffer[consoleBufferSize] = c;
    consoleBufferSize++;
  }
}

void Interpret_Message (Message* message) {
  
//  Serial.println ((*message).source);
//  Serial.println ((*message).destination);
  
  // Check if the message is from the local "serial" channel
  if ((*message).source == (*message).destination) { // TODO: Update this. Add concept of "channel" possibly. Or make EVERYTHING text based and virtual (THIS ONE!).
  
    // TODO: Don't separate "shell" behavior from other behaviors!
    Perform_Shell_Behavior ((*message).content);
    
  //} else if (((*message).source != platformUuid) && ((*message).destination == platformUuid || (*message).destination == BROADCAST_ADDRESS)) { // TODO: Update this, too! (see previous "if" comment)
  } else if ((*message).source != platformUuid) { // TODO: Update this, too! (see previous "if" comment)

    // Check if the message is from the remote "mesh" channel
    
    if (strncmp ((*message).content, "notice presence", (*message).size) == 0) {  
      Serial.println ("notice presence");
      
      Handle_Message_Active (message);
    }
    
    else if (strncmp ((*message).content, "ping", (*message).size) == 0) {  
      Serial.println ("ping");
      
      // TODO: Send module to remote module to set up its "observerAddress"
      Message* outgoingMessage = Create_Message (platformUuid, perspectiveAddress, String ("pong"));
      Queue_Outgoing_Message (outgoingMessage);
      
    } else if (strncmp ((*message).content, "pong", (*message).size) == 0) {  
      
      Serial.println ("pong");
      
      // TODO: Send module to remote module to set up its "observerAddress"
      Message* outgoingMessage = Create_Message (platformUuid, perspectiveAddress, String ("pong"));
      Queue_Outgoing_Message (outgoingMessage);
    }
    
    else if (strncmp ((*message).content, "start sharing with", 18 /* (*message).size */) == 0) {  
      
      String fourthWord = getValue ((*message).content, ' ', 3);
      
      Serial.println (String ("starting to share with ") + String (fourthWord) + String ("."));
      
      observerAddress = fourthWord.toInt ();
      
      // TODO: Send module to remote module to set up its "observerAddress"
      Message* outgoingMessage = Create_Message (platformUuid, observerAddress, String ("started sharing"));
      Queue_Outgoing_Message (outgoingMessage);
      
    } else if (strncmp ((*message).content, "started sharing", (*message).size) == 0) {  
      
      int address = (*message).source;
      perspectiveAddress = address;
      
      Serial.print ("Entered module ");
      Serial.print (perspectiveAddress);
      Serial.print (".\n");
    
    }
    
    else if (strncmp ((*message).content, "notice gesture swing", (*message).size) == 0) {
      Serial.println ("notice gesture swing");
      Handle_Message_Swing (message);
    } else if (strncmp ((*message).content, "notice gesture shake", (*message).size) == 0) {
      Serial.println ("notice gesture shake");
      Handle_Message_Shake (message);
    } else if (strncmp ((*message).content, "notice gesture tap", (*message).size) == 0) {
      Serial.println ("notice gesture tap");
      Handle_Message_Tap (message);
    }
    
    else if (strncmp ((*message).content, "notice gesture tap as left", (*message).size) == 0) {
      Serial.println ("announce gesture tap as left");
      Handle_Message_Tap_To_Another_As_Left (message);
    } else if (strncmp ((*message).content, "request confirm gesture tap as right", (*message).size) == 0) {
      Serial.println ("request confirm gesture tap as right");
      Handle_Message_Request_Confirm_Tap_To_Another_As_Right (message);
    } else if (strncmp ((*message).content, "confirm gesture tap as left", (*message).size) == 0) {
      Serial.println ("confirm gesture tap as left");
      Handle_Message_Confirm_Tap_To_Another_As_Left (message);
    }
    
//    else if (strncmp ((*message).content, "notice gesture tap", (*message).size) == 0) {
//      Serial.print ("notice gesture tap");
//      Handle_Message_Tap_To_Another_As_Right (message);
//    }
    
    else if (strncmp ((*message).content, "notice gesture tap as right", (*message).size) == 0) {
      Serial.println ("announce gesture tap as right");
      Handle_Message_Tap_To_Another_As_Right (message);
    } else if (strncmp ((*message).content, "request confirm gesture tap as left", (*message).size) == 0) {
      Serial.println ("request confirm gesture tap as left");
      Handle_Message_Request_Confirm_Tap_To_Another_As_Left (message);
    } else if (strncmp ((*message).content, "confirm gesture tap as right", (*message).size) == 0) {
      Serial.println ("confirm gesture tap as right");
      Handle_Message_Confirm_Tap_To_Another_As_Right (message);
    }
    
    else if (strncmp ((*message).content, "request confirm gesture tap", (*message).size) == 0) {
      Serial.println ("request confirm gesture tap");
      Handle_Message_Request_Confirm_Tap (message);
    } else if (strncmp ((*message).content, "request confirm gesture tap", (*message).size) == 0) {
      Serial.println ("confirm gesture tap");
      Handle_Message_Confirm_Tap (message);
    } 
    
    else if (strncmp ((*message).content, "turn output off", (*message).size) == 0) { // activate module output
      Serial.println ("turn on output");
      
      // ACTIVATE_MODULE_OUTPUT
//      Update_Channel_Value (MODULE_OUTPUT_PIN, PIN_VALUE_HIGH);
//      syncPinValue(MODULE_OUTPUT_PIN);
      Channel* moduleOutputChannel = Get_Channel (platform, MODULE_OUTPUT_PIN);
      Update_Channel_Value (moduleOutputChannel, PIN_VALUE_HIGH);
      Propagate_Channel_Value (moduleOutputChannel);
    } else if (strncmp ((*message).content, "turn output off", (*message).size) == 0) { // deactivate module output
      Serial.println ("turn output off");
      
//      Update_Channel_Value (MODULE_OUTPUT_PIN, PIN_VALUE_LOW);
//      syncPinValue(MODULE_OUTPUT_PIN);
      Channel* moduleOutputChannel = Get_Channel (platform, MODULE_OUTPUT_PIN);
      Update_Channel_Value (moduleOutputChannel, PIN_VALUE_LOW);
      Propagate_Channel_Value (moduleOutputChannel);
    }
    
    else {
//      Serial.print ((*message).content);
      Perform_Shell_Behavior ((*message).content);
    }
    
  }

  Delete_Message (message);
  
}

// TODO: Make this callable remotely from other nodes...
// TODO: Add command to set default module (e.g., "enter"), and return to the current module (e.g., "exit")
void Perform_Shell_Behavior (String message) {
  
  // Echo the message
  Serial.print ("> ");
  Serial.print (message);
  Serial.print ("\n");
  
  int wordCount = getValueCount (message, ' ');
  String firstWord = getValue (message, ' ', 0);
  
  //!
  //! Parse and process the message
  //!
  
  // "to ..."
  // e.g.,
  // "to 34 turn light off"
  
  if (firstWord.compareTo ("to") == 0) {
    
    String destination = getValue (message, ' ', 1);
    int destinationAddress = -1;
    if (destination.compareTo ("all") == 0) {
      destinationAddress = BROADCAST_ADDRESS;
    } else {
      // TODO: Check if it's a name, and if so, look up its address in a lookup table (or request address first)
      // TODO: Check if it's a number, and if so, convert it to an integer.
      destinationAddress = destination.toInt ();
    }
    
    String outgoingMessageContent = getValueRest (message, ' ', 2);
    
    Serial.print ("DESTINATION:"); Serial.print (destinationAddress); Serial.print ("\n");
    Serial.print ("REMAINDER:"); Serial.print (outgoingMessageContent); Serial.print ("\n");
    
    // Send to mesh
    Queue_Message (platformUuid, destinationAddress, outgoingMessageContent);
    
    // Perform behavior locally (if broadcast)
    if (destinationAddress == BROADCAST_ADDRESS) {
      //Message* selfMessage = Create_Message (platformUuid, destinationAddress, outgoingMessageContent);
      Message* selfMessage = Create_Message (destinationAddress, destinationAddress, outgoingMessageContent);
      Queue_Incoming_Message (selfMessage);
//      Perform_Shell_Behavior (outgoingMessageContent);
    }
    
  } else if (firstWord.compareTo ("ip") == 0) {
    
    Serial.println (ipAddress);
    
  } else if (firstWord.compareTo ("self") == 0) { // self
    
    Serial.println (name);
    Serial.println (platformUuid);
    
  } else if (firstWord.compareTo ("neighbors") == 0) { // others
    
    for (int i = 0; i < neighborCount; i++) {
      Serial.print (i);
      Serial.print ("\t");
      Serial.print (neighbors[i]);
      Serial.print ("\n");
    }
    
  } else if (firstWord.compareTo ("outputs") == 0) {
    
    for (int i = 0; i < nextModuleCount; i++) {
      Serial.print (i);
      Serial.print ("\t");
      Serial.print (nextModules[i]);
      Serial.print ("\n");
    }
    
  } else if (firstWord.compareTo ("inputs") == 0) {
    
    for (int i = 0; i < previousModuleCount; i++) {
      Serial.print (i);
      Serial.print ("\t");
      Serial.print (previousModules[i]);
      Serial.print ("\n");
    }
    
  }
  
  // "turn ..."
  // e.g.,
  // "turn light on" and "turn light off"
  // "turn input on" and "turn input off"
  // "turn output on" and "turn output off"
  // "turn wifi on" and "turn wifi off"
  // "turn mesh on" and "turn mesh off"
  
  else if (firstWord.compareTo ("turn") == 0) { // i.e., switch, set
    
    String secondWord = getValue (message, ' ', 1);
    
    if (secondWord.compareTo ("input") == 0) {
      
      String thirdWord = getValue (message, ' ', 2);
    
      if (thirdWord.compareTo ("light") == 0) {
        
        String fourthWord = getValue (message, ' ', 3);
        
        if (fourthWord.compareTo ("on") == 0) {
        
          Update_Input_Color (255, 255, 255);
          
          Serial.println ("Turning input light on.");
          
        } else if (fourthWord.compareTo ("off") == 0) {
        
          Update_Input_Color (0, 0, 0);
          
          Serial.println ("Turning input light off.");
          
        } 
        
      } if (thirdWord.compareTo ("channel") == 0) { // TODO: Make this optional or less abstract (optionally)!
        
        // TODO: implement "on" and "off" and analog input and output
        
      }
      
    } else if (secondWord.compareTo ("output") == 0) {
      
      String thirdWord = getValue (message, ' ', 2);
    
      if (thirdWord.compareTo ("light") == 0) {
        
        String fourthWord = getValue (message, ' ', 4);
        
        if (fourthWord.compareTo ("on") == 0) {
        
          Update_Output_Color (255, 255, 255);
          
          Serial.println ("Turning output light on.");
          
        } else if (fourthWord.compareTo ("off") == 0) {
        
          Update_Output_Color (0, 0, 0);
          
          Serial.println ("Turning output light off.");
          
        } 
      } 
      
    } else if (secondWord.compareTo ("light") == 0) {
      
      String thirdWord = getValue (message, ' ', 2);
      
      if (thirdWord.compareTo ("on") == 0) {
        
        Update_Input_Color (255, 255, 255);
        Update_Output_Color (255, 255, 255);
        
        Serial.println ("Turning light on.");
        
      } else if (thirdWord.compareTo ("off") == 0) {
        
        Update_Input_Color (0, 0, 0);
        Update_Output_Color (0, 0, 0);
        
        Serial.println ("Turning light off.");
        
      } 
    }
  } 
  
  // "change ..."
  // e.g.,
  // "change color to red"
  // "change color to #ffffff"
  // "change color to 255,255,255"
  // "change input color to 255,128,128"
  // "change output color to orange
  
  else if (firstWord.compareTo ("change") == 0) { // i.e., update
    
    String secondWord = getValue (message, ' ', 1);
    
    // "change input ..."
    if (secondWord.compareTo ("input") == 0) {
      
      String thirdWord = getValue (message, ' ', 2);
      
      // "change input color ..."
      if (thirdWord.compareTo ("color") == 0) {
      
        String fourthWord = getValue (message, ' ', 3); // i.e., "to" or the color
        
        // "change input color (to) [color]"
        
        // Parse the color
        int red   = getValue (message, ' ', 4).toInt ();
        int green = getValue (message, ' ', 5).toInt ();
        int blue  = getValue (message, ' ', 6).toInt ();
        
        Update_Input_Color (red, green, blue);
        
        Serial.println ("Changing input color.");
        
      }
      
    } else if (secondWord.compareTo ("output") == 0) {
      
      String thirdWord = getValue (message, ' ', 2);
      
      // "change input color ..."
      if (thirdWord.compareTo ("color") == 0) {
      
        String fourthWord = getValue (message, ' ', 3); // i.e., "to" or the color
        
        // "change input color (to) [color]"
        
        // Parse the color
        int red   = getValue (message, ' ', 4).toInt ();
        int green = getValue (message, ' ', 5).toInt ();
        int blue  = getValue (message, ' ', 6).toInt ();
        
        Update_Output_Color (red, green, blue);
        
        Serial.println ("Changing output color.");
        
      }
      
    } else if (secondWord.compareTo ("color") == 0) {
      
      String thirdWord = getValue (message, ' ', 2); // i.e., "to" or the color
      
      // "change input color (to) [color]"
      
      // Parse the color
      int red   = getValue (message, ' ', 3).toInt ();
      int green = getValue (message, ' ', 4).toInt ();
      int blue  = getValue (message, ' ', 5).toInt ();
      
      Update_Input_Color (red, green, blue);
      Update_Output_Color (red, green, blue);
      
      Serial.println ("Changing output color.");
      
    } 
  }
  
  else if (firstWord.compareTo ("rename") == 0) {
    
    name = Generate_Name ();
    Serial.println (name);
    
  }
  
  // "change ..."
  // e.g.,
  // "change color to red"
  // "change color to #ffffff"
  // "change color to 255,255,255"
  // "change input color to 255,128,128"
  // "change output color to orange
  
  else if (firstWord.compareTo ("play") == 0) {
    
    // e.g., "play note 1047 1000"
    String sound = getValue (message, ' ', 1);
    int note = getValue (message, ' ', 2).toInt ();
    int duration = getValue (message, ' ', 3).toInt ();
    Play_Note (note, duration);
//          delay (1000);
//          Stop_Sound ();

  } else if (firstWord.compareTo ("show") == 0) { // i.e., echo, print, show, display
    
    String secondWord = getValue (message, ' ', 1);
    
    if (secondWord.compareTo ("orientation") == 0) {
    
      Serial.print ("(");
      Serial.print (roll); Serial.print (", ");
      Serial.print (pitch); Serial.print (", ");
      Serial.print (yaw); Serial.print (")\n");
      
      // TODO: Considering adding "as json" and "as xml" and similar modifiers
      
    } else if (secondWord.compareTo ("perspective") == 0) {
      
      Serial.println (perspectiveAddress);
      
    } else if (secondWord.compareTo ("channel") == 0) {
      
      String thirdWord = getValue (message, ' ', 2);
      int channelAddress = thirdWord.toInt ();
      
      Channel* channel = Get_Channel (channelAddress);
      
      if (channel != NULL) {
        Serial.print ("Channel ");
        Serial.print (channelAddress);
        Serial.print (" is ");
        Serial.print ((*channel).value);
        Serial.print (".\n");
      }
      
    } else if (secondWord.compareTo ("input") == 0) {
      
      String thirdWord = getValue (message, ' ', 2);
      
      if (thirdWord.compareTo ("color") == 0) {
        Serial.print (targetInputColor[0]);
        Serial.print (" ");
        Serial.print (targetInputColor[1]);
        Serial.print (" ");
        Serial.print (targetInputColor[2]);
        Serial.print (" ");
      }
      
    } else if (secondWord.compareTo ("output") == 0) {
      
      String thirdWord = getValue (message, ' ', 2);
      
      if (thirdWord.compareTo ("color") == 0) {
        Serial.print (targetOutputColor[0]);
        Serial.print (" ");
        Serial.print (targetOutputColor[1]);
        Serial.print (" ");
        Serial.print (targetOutputColor[2]);
        Serial.print (" ");
      }
      
    }
    
  } else if (firstWord.compareTo ("find") == 0) { // i.e., "ping", "search"
  
    int destination = BROADCAST_ADDRESS;
    
    int wordCount = getValueCount (message, ' ');
    
    //! Send to specific module
    if (wordCount > 1) {
      
      String secondWord = getValue (message, ' ', 1);
      
      if (secondWord.compareTo ("all") != 0) {
        destination = getValue (message, ' ', 1).toInt ();
      }
      
      // TODO: Send module to remote module to set up its "observerAddress"
      Message* outgoingMessage = Create_Message (platformUuid, destination, String ("ping"));
      Queue_Outgoing_Message (outgoingMessage);
      
      Serial.print ("Finding module ");
      Serial.print (destination);
      Serial.print (".");
      
    } 
    
    //! Broadcast
    else {
      
      // TODO: Send module to remote module to set up its "observerAddress"
      Message* outgoingMessage = Create_Message (platformUuid, destination, String ("ping"));
      Queue_Outgoing_Message (outgoingMessage);
      
      Serial.println ("Finding other modules.");
      
    }
    
  } else if (firstWord.compareTo ("enter") == 0) { // i.e., select
    
    // e.g., "enter neighbor 34"
    
    int address = getValue (message, ' ', 1).toInt ();
//    perspectiveAddress = address;
    
    // TODO: Send module to remote module to set up its "observerAddress"
    Message* outgoingMessage = Create_Message (platformUuid, address, String ("start sharing with ") + String (platformUuid));
    Queue_Outgoing_Message (outgoingMessage);
    
//    Serial.print ("Entering module ");
//    Serial.print (perspectiveAddress);
//    Serial.print (".");
    
  } else if (firstWord.compareTo ("exit") == 0) { // i.e., leave
    
    // Send module to remote module to set up its "observerAddress"
    Message* outgoingMessage = Create_Message (platformUuid, perspectiveAddress, String ("stop sharing with ") + String (platformUuid));
    Queue_Outgoing_Message (outgoingMessage);
    
    // e.g., "exit"
    perspectiveAddress = platformUuid;
    
//    Serial.print ("Exited module ");
//    Serial.print (perspectiveAddress);
//    Serial.print (".");
    
  } else if (firstWord.compareTo ("remember") == 0) { // i.e., learn, store, remember
    
    // Add (key, value) pair to memory
    String trigger = getValue (message, ' ', 1);
    String content = getValue (message, ' ', 2);
    
    // Send module to remote module to set up its "observerAddress"
    Memory* memory = Create_Memory (trigger, content);
    Append_Memory (memory);
    
  } else if (firstWord.compareTo ("forget") == 0) { // i.e., remember, recall, load
    
    // Add (key, value) pair to memory
    String trigger = getValue (message, ' ', 1);
    
    // Send module to remote module to set up its "observerAddress"
    const int triggerBufferSize = 64;
    char triggerChar[triggerBufferSize];
    trigger.toCharArray (triggerChar, triggerBufferSize);
    Memory* memory = Remove_Memory (triggerChar);
    
    if (memory != NULL) {
      Serial.print ("Deleting memory ");
      Serial.print ((*memory).trigger);
      Serial.print (" -> ");
      Serial.print ((*memory).content);
      Serial.print ("\n");
    }
    
    Delete_Memory (memory);
    
  } else if (firstWord.compareTo ("recall") == 0) {
    
    // TODO: Recall (key, value) pair by key
    // Add (key, value) pair to memory
    String trigger = getValue (message, ' ', 1);
    
    // Send module to remote module to set up its "observerAddress"
    const int triggerBufferSize = 64;
    char triggerChar[triggerBufferSize];
    trigger.toCharArray (triggerChar, triggerBufferSize);
    Memory* memory = Get_Memory (triggerChar);
    
    if (memory != NULL) {
      Serial.print ((*memory).trigger);
      Serial.print (" -> ");
      Serial.print ((*memory).content);
      Serial.print ("\n");
    }
    
  } else if (firstWord.compareTo ("generalize") == 0) { // generalize upon memory/KB (using FOL or similar kinds of techniques), and verify with other people that inferrences are correct
    
    // TODO: Prefix command with "propagate" to broadcast
    
  } else if (firstWord.compareTo ("subscribe") == 0) { // this is the same as mirror? or is subscribe only subscribing from behavior changes from now on?
    
    // TODO: Add (key, value) pair to memory
    
  } else if (firstWord.compareTo ("unsubscribe") == 0) {
    
    // TODO: Add (key, value) pair to memory
    
  } else if (firstWord.compareTo ("learn pattern") == 0) { // learn patterns (i.e., model a pattern) for gestures, sensor analog sensor patterns, etc.
    
    // TODO: Prefix command with "propagate" to broadcast
    
  } else if (firstWord.compareTo ("associate") == 0) { // associate observed input with outputs to create a "mapping" that updates the outputs to best match the inputs based on the mapping just created. consider allowing them to be named.
    
    // TODO: Prefix command with "propagate" to broadcast
    
  } else if (firstWord.compareTo ("propagate") == 0) {
    
    // TODO: Prefix command with "propagate" to broadcast
    
  } else if (firstWord.compareTo ("mirror") == 0) {
    
    // TODO: Prefix command with "propagate" to broadcast
    
  } else if (firstWord.compareTo ("mimmic") == 0) {
    
    // TODO: Prefix command with "propagate" to broadcast
    
  } else if (firstWord.compareTo ("imagine") == 0) { // simulate --> creates a simulated programmable machine that can be enacted on this device
    
    // TODO: Prefix command with "propagate" to broadcast
    
  } else if (firstWord.compareTo ("pretend") == 0) { // enacts a simulated machine on this hardware while preserving the one currently on the device for easy reversion
    
    // TODO: Prefix command with "propagate" to broadcast
    
  } else if (firstWord.compareTo ("distribute") == 0) { // distributes the behaviors on all modules across all moduels after scheduling, to make the overall operation more efficient (i.e., the moduels coordinate and collaborate)
    
    // TODO: Prefix command with "propagate" to broadcast
    
  } else if (firstWord.compareTo ("reboot") == 0) {
    
    Serial.println ("BBL.");
    Restart ();
    
  } else {
    
    Serial.println ("That doesn't do anything.");
    
  }
}

#endif
