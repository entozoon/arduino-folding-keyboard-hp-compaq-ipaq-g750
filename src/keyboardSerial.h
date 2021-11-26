#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial keySerial(9, 10); // RX (D2), TX
typedef struct {
  int lowerCase;
  int upperCase;
  bool pressed;
  uint8_t down;
  uint8_t up;
} Key;
Key keys[]{
    {'a', 'A', false, 156, 140},
    {'b', 'B', false, 51, 19},
    {KEY_LEFT_SHIFT, 0, false, 59, 27},
    {KEY_CAPS_LOCK, 0, false, 74, 66},
};
// Find index for special chars
uint8_t findIndex(int key) {
  uint8_t index = 255; // 255=Unknown (shonky but keeping memory down)
  for (uint8_t i = 0; i < sizeof(keys) / sizeof(Key); i++) {
    // Only checks lowerCase
    if (key == keys[i].lowerCase) {
      index = i;
    }
  }
  return index;
}
Key findKey(int key) {
  for (uint8_t i = 0; i < sizeof(keys) / sizeof(Key); i++) {
    // Only checks lowerCase
    if (key == keys[i].lowerCase) {
      return keys[i];
    }
  }
}
uint8_t inArray(String key) {
  uint8_t index = 255; // 255=Unknown (shonky but keeping memory down)
  for (uint8_t i = 0; i < sizeof(keys) / sizeof(Key); i++) {
    // Only check lowerCase
    if (key == keys[i].lowerCase) {
      index = i;
    }
  }
  return index;
}
int modifiers[] = {KEY_LEFT_SHIFT, KEY_LEFT_SHIFT};
uint8_t indexShift = findIndex(KEY_LEFT_SHIFT);
uint8_t indexCapsLock = findIndex(KEY_LEFT_SHIFT);
bool debugging = false;
bool capsLock = false;
void keyboardSerialInit() {
  keySerial.begin(4800);
  keySerial.listen();
}
char keyboardSerialEcho() {
  if (keySerial.available()) {
    uint8_t action = keySerial.read();
    // For every set (nb: sizeof includes all nested items)
    bool keyFound = false;
    for (uint8_t i = 0; i < sizeof(keys) / sizeof(Key); i++) {
      Key &key = keys[i];
      bool capitalize = findKey(KEY_LEFT_SHIFT).pressed || capsLock;
      if (action == key.down && !key.pressed) {
        if (key.lowerCase == KEY_LEFT_SHIFT) {
          capsLock = !capsLock;
        }
        key.pressed = true;
        keyFound = true;
        debugging &&Serial.print("[v] ");
        Serial.print(capitalize ? key.upperCase : key.lowerCase);
        debugging &&Serial.println("");
        return capitalize ? key.upperCase : key.lowerCase;
      } else if (action == key.up && key.pressed) {
        key.pressed = false;
        keyFound = true;
        debugging &&Serial.print("[^] ");
        debugging &&Serial.println(capitalize ? key.upperCase : key.lowerCase);
      }
    }
    if (!keyFound) {
      debugging &&Serial.print("Unknown: ");
      debugging &&Serial.println(action);
    }
  }
}