#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial keySerial(2, 3); // RX (D2), TX
void setup()
{
  Serial.begin(115200);
  keySerial.begin(4800);
  keySerial.listen();
  delay(2000);
}
void loop()
{
  if (keySerial.available())
  {
    String keyData = String(keySerial.read(), HEX);
    Serial.println(keyData);
  }