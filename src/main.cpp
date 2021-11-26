#include <Arduino.h>
#include <Keyboard.h>
#include <keyboardSerial.h>
void setup() {
  Serial.begin(115200);
  keyboardSerialInit();
  Keyboard.begin();
  delay(10000);
  Serial.println("Let's go!");
}
void loop() {
  int c = keyboardSerialEcho();
  // Keyboard.write('!');
  if (c && c != 0) {
    Keyboard.write(c);
    Serial.print(char(c));
  }
  delay(10);
}