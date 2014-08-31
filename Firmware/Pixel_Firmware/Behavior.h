#ifndef BEHAVIOR_H
#define BEHAVIOR_H

// Instruction operation codes (op. codes)
#define PIN_READ_DIGITAL 0
#define PIN_WRITE_DIGITAL 1
#define BEHAVIOR_DELAY 2
#define BEHAVIOR_ERASE 3
#define BEHAVIOR_DELETE 4
#define BEHAVIOR_UPDATE 5
#define BEHAVIOR_REBOOT 20
#define STATUS_WIFI_CONNECTED 30

// turn digital pin on
// turn digital pin off
// get state of digital pin
// delay

int behaviorCount = 0;
// Generates unique behavior ID
int generateBehaviorIdentifier() {
  int behaviorIdentifier = behaviorCount;
  behaviorCount++;
  return behaviorIdentifier;
}

struct Behavior {
  // TODO: add "instruction" so can add "delay" etc.
  int uid; // The behavior's unique ID (uid will recur on other modules since it's just a counter associated with behaviors added)
  int operation; // i.e., write, read, PWM, "remember value at this time"
  int pin; // The pin number
  int type; // i.e., digital or analog
  int mode; // i.e., input or output
  int value; // i.e., high or low
};

// "Delay"

struct Delay {
  int startTime; // i.e., write, read, PWM, "remember value at this time"
  int duration;
  Behavior *behavior;
};

#define DELAY_LIMIT 20
Delay delays[DELAY_LIMIT];
int delayCount = 0;

#endif