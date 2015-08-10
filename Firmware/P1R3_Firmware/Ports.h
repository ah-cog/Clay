#ifndef PORTS_H
#define PORTS_H

#ifndef INPUT
  #define INPUT 0
#endif
#ifndef OUTPUT
  #define OUTPUT 1
#endif

#include <stdarg.h>

#define PIN_COUNT 8
int pinAddresses[PIN_COUNT];
int pinModes[PIN_COUNT]; // 0=NONE, 1=INPUT, 2=OUTPUT
int pinValues[PIN_COUNT];

void Setup_Pins (int n_args, ...) {

  // Assign physical MCU pins to Clay's I/O
  va_list ap;
  va_start (ap, n_args);
  for (int i = 0; i < n_args; i++) {
    pinAddresses[i] = va_arg (ap, int);
  }
  va_end (ap);
  
}

void Set_Pin (int number, int mode, int value) {
  Serial.println ("Set_Pin");
  pinModes[(pinAddresses[number])] = mode;
  pinMode (pinAddresses[number], mode);
  
  Serial.println ("number = " + String (number));
  Serial.println ("pinAddresses[number] = " + String (pinAddresses[number]));
  Serial.println ("pinModes[(pinAddresses[number])] = " + String (pinModes[(pinAddresses[number])]));

  if (pinModes[(pinAddresses[number])] == OUTPUT) {
    pinValues[(pinAddresses[number])] = value;
    digitalWrite (pinAddresses[number], pinValues[(pinAddresses[number])]);
  }
}

int Get_Pin_Address (int number) {
  return pinAddresses[number];
}

int Get_Pin_Mode (int number) {
  return pinModes[number];
}

int Get_Pin_Value (int number) {

  if (pinModes[(pinAddresses[number])] == INPUT) {
    pinValues[(pinAddresses[number])] = digitalRead (pinAddresses[number]);
    return pinValues[(pinAddresses[number])];
  } else if (pinModes[(pinAddresses[number])] == OUTPUT) {
    return pinValues[(pinAddresses[number])];
  }

  return -1;
}

#endif
