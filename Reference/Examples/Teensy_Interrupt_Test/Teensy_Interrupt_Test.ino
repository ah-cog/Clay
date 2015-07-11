const byte LED = 13;

int inputPin = 14; // 0

void inputISR (void) {
  static boolean state = false;
  state = !state; // toggle
  digitalWrite (LED, state ? HIGH : LOW);
}

void setup() {
  pinMode (LED, OUTPUT);

  pinMode (inputPin, INPUT);
  // attachInterrupt(inputPin, inputISR, FALLING); // interrrupt 1 is data ready
  // attachInterrupt(inputPin, inputISR, LOW); // interrrupt 1 is data ready
  // attachInterrupt(inputPin, inputISR, HIGH); // interrrupt 1 is data ready
  attachInterrupt(inputPin, inputISR, RISING); // interrrupt 1 is data ready
}

void loop () {
  // Nothing is needed here, beceause it's handled in the interrupts!
}
