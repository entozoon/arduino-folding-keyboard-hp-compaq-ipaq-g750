#include <Arduino.h>
// Basic bitch debug *********
#include <SoftwareSerial.h>
SoftwareSerial keySerial(9, 10); // RX, TX
void setup() {
  Serial.begin(115200);
  delay(2000);
  keySerial.begin(4800);
  keySerial.listen();
}
void loop() {
  if (keySerial.available()) {
    Serial.println(keySerial.read());
  }
}
// ***************************
//
// #include <Keyboard.h>
// #include <keyboardSerial.h>
// void setup() {
//   Serial.begin(115200);
//   keyboardSerialInit();
//   Keyboard.begin();
//   delay(10000);
//   Serial.println("Let's go!");
// }
// void loop() {
//   int c = keyboardSerialEcho();
//   // Keyboard.write('!');
//   if (c && c != 0) {
//     Keyboard.write(c);
//     Serial.print(char(c));
//   }
//   delay(10);
// }