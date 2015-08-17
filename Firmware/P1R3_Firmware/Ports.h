#ifndef PORTS_H
#define PORTS_H

#ifndef INPUT
  #define INPUT 0
#endif
#ifndef OUTPUT
  #define OUTPUT 1
#endif

#include <stdarg.h>

#define PORT_COUNT 8
//int pinAddresses[PORT_COUNT];
//int pinModes[PORT_COUNT]; // 0=NONE, 1=INPUT, 2=OUTPUT
//int pinValues[PORT_COUNT];

struct Port {
  int address; // The physical device's pin.
  int mode; // 0=NONE, 1=INPUT, 2=OUTPUT
  int value;
};

Port ports[PORT_COUNT];

void Setup_Pins (int n_args, ...) {

  // Assign physical MCU pins to Clay's I/O
  va_list ap;
  va_start (ap, n_args);
  for (int i = 0; i < n_args; i++) {
//    pinAddresses[i] = va_arg (ap, int);
    ports[i].address = va_arg (ap, int);
    ports[i].mode = OUTPUT;
  }
  va_end (ap);
  
}

void Set_Pin (int number, int mode, int value) {
  Serial.println ("Set_Pin");
//  pinModes[(pinAddresses[number])] = mode;
  ports[number].mode = mode;
//  pinMode (pinAddresses[number], mode);
  pinMode (ports[number].address, mode);
  
//  Serial.println ("number = " + String (number));
//  Serial.println ("pinAddresses[number] = " + String (pinAddresses[number]));
//  Serial.println ("pinModes[(pinAddresses[number])] = " + String (pinModes[(pinAddresses[number])]));
  Serial.println ("number = " + String (number));
  Serial.println ("ports[number].address = " + String (ports[number].address));
  Serial.println ("ports[number].mode = " + String (ports[number].mode));

  //if (pinModes[(pinAddresses[number])] == OUTPUT) {
  if (ports[number].mode == OUTPUT) {
//    pinValues[(pinAddresses[number])] = value;
    ports[number].value = value;
//    digitalWrite (pinAddresses[number], pinValues[(pinAddresses[number])]);
    digitalWrite (ports[number].address, ports[number].value);
  }
}

int Get_Pin_Address (int number) {
//  return pinAddresses[number];
  return ports[number].address;
}

int Get_Pin_Mode (int number) {
//  return pinModes[number];
  return ports[number].mode;
}

int Get_Pin_Value (int number) {

//  if (pinModes[(pinAddresses[number])] == INPUT) {
  if (ports[number].mode == INPUT) {
    // pinValues[(pinAddresses[number])] = digitalRead (pinAddresses[number]);
    ports[number].value = digitalRead (ports[number].address);
//    return pinValues[(pinAddresses[number])];
    return ports[number].value;
  //} else if (pinModes[(pinAddresses[number])] == OUTPUT) {
  } else if (ports[number].mode == OUTPUT) {
    //return pinValues[(pinAddresses[number])];
    return ports[number].value;
  }

  return -1;
}

#endif
