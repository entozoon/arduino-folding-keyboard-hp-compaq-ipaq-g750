#include <Arduino.h>
#include <Keyboard.h>
#include <keyboardSerial.h>
void setup() {
  Serial.begin(115200);
  keyboardSerialInit();
  Keyboard.begin();
  delay(20000);
}
void loop() {
  int c = keyboardSerialEcho();
  // Keyboard.write('!');
  if (c) {
    Keyboard.write(c);
  }
}