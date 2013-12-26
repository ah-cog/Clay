/*
 * Uuid
 *
 * UUIDs are unique numbers that are used for identifying individual units,
 * functions, programmes, or whatever you want to tag.
 *
 * In this demo, press the Arduino Reset button to generate a new number.
 *
 * UUIDs can be assigned sequentially from allocated blocks of numbers, but
 * they are most powerful when randomly assigned. UUIDs are such big numbers
 * that, for all effective purposes, no two numbers will ever match.
 *
 * UUIDs are particularly useful in web-aware devices, or radio networks.
 *
 * For a discussion of the use of UUIDs, see
 *   http://en.wikipedia.org/wiki/Universally_Unique_Identifier
 *
 * For implementation details of UUIDs, see
 *   http://tools.ietf.org/html/rfc4122
 */
 
void generateUuid(byte* uuidNumber, int length) {
    for (int i = 0; i < 16; i++) {
        uuidNumber[i] = (byte) random(0x00, 0xFF);
    }
}

void prinUuidtHex(byte number) {
  int topDigit = number >> 4;
  int bottomDigit = number & 0x0f;
  // Print high hex digit
  Serial.print( "0123456789ABCDEF"[topDigit] );
  // Low hex digit
  Serial.print( "0123456789ABCDEF"[bottomDigit] );
}

void printUuid(byte* uuidNumber) {
  int i;
  for (i=0; i<16; i++) {
    if (i==4) Serial.print("-");
    if (i==6) Serial.print("-");
    if (i==8) Serial.print("-");
    if (i==10) Serial.print("-");
    prinUuidtHex(uuidNumber[i]);
  }
}