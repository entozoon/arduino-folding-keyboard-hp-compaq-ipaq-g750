#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial keySerial(9, 10); // RX (D2), TX
typedef struct {
  uint8_t lowerCase;
  uint8_t upperCase;
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
uint8_t modifiers[] = {KEY_LEFT_SHIFT, KEY_CAPS_LOCK};
bool debugging = false;
bool debuggingHeavy = false;
// Find index for special chars
uint8_t findKeyIndexFromAction(uint8_t action) {
  for (uint8_t i = 0; i < sizeof(keys) / sizeof(Key); i++) {
    if (keys[i].down == action || keys[i].up == action) {
      return i;
    }
  }
  return 255; // 255=Unknown (shonky but keeping memory down)
}
Key &findKey(uint8_t key) {
  for (uint8_t i = 0; i < sizeof(keys) / sizeof(Key); i++) {
    // Only checks lowerCase
    if (key == keys[i].lowerCase) {
      return keys[i];
    }
  }
}
bool inArray(uint8_t needle, uint8_t haystack[]) {
  bool found = false;
  for (uint8_t i = 0; i < sizeof(haystack); i++) {
    if (haystack[i] == needle) {
      found = true;
    }
  }
  return found;
}
bool capsLock = false;
void keyboardSerialInit() {
  keySerial.begin(4800);
  keySerial.listen();
}
char keyboardSerialEcho() {
  if (keySerial.available()) {
    uint8_t action = keySerial.read();
    // For every set (nb: sizeof includes all nested items)
    uint8_t keyIndex = findKeyIndexFromAction(action);
    if (debuggingHeavy) {
      Serial.print("\n\nAction: ");
      Serial.print(action);
      Serial.print("\nkeyIndex: ");
      Serial.print(keyIndex);
    }
    bool keyFound = keyIndex != 255;
    if (keyFound) {
      // Key &actionKey = findKey(action);
      Key &actionKey = keys[keyIndex];
      bool capitalize = findKey(KEY_LEFT_SHIFT).pressed || capsLock;
      if (action == actionKey.down && !actionKey.pressed) {
        if (actionKey.lowerCase == KEY_CAPS_LOCK) {
          capsLock = !capsLock;
          debugging &&capsLock ? Serial.print("[CAPS]")
                               : Serial.print("[!CAPS]");
        }
        actionKey.pressed = true;
        keyFound = true;
        if (debugging) {
          Serial.print(F("([v]"));
          Serial.print(capitalize ? char(actionKey.upperCase)
                                  : char(actionKey.lowerCase));
          Serial.print(F(") "));
        }
        if (!inArray(actionKey.lowerCase, modifiers)) {
          return capitalize ? actionKey.upperCase : actionKey.lowerCase;
        }
      } else if (action == actionKey.up && actionKey.pressed) {
        actionKey.pressed = false;
        keyFound = true;
        if (debugging) {
          Serial.print(F("([^]"));
          Serial.print(capitalize ? char(actionKey.upperCase)
                                  : char(actionKey.lowerCase));
          Serial.print(F(") "));
        }
      }
    } else {
      debuggingHeavy &&Serial.print(F("(Unexpected:"));
      debuggingHeavy &&Serial.print(action);
      debuggingHeavy &&Serial.print(F(") "));
    }
  }
  return 0;
}