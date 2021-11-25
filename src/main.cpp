#include <Arduino.h>
const int pinTestsLength = 5;
const int pinTests[pinTestsLength] = {LED_BUILTIN, 0, 1, 2, 3};
void setup()
{
  Serial.begin(115200); // 76800 is good for esp, as it boots in this. need to update serial monitor bitch
  // Spews gargage in serial monitor after upload but.. should calm down and work; certainly after a reset. No idea why (might just be platformio)
  delay(4000); // Pause for upload issues
  Serial.println("\nLet's go!");
  for (int i = 0; i < pinTestsLength; i++)
  {
    Serial.print("Init ");
    Serial.println(pinTests[i]);
    pinMode(pinTests[i], OUTPUT);
  }
}
void loop()
{
  for (int i = 0; i < pinTestsLength; i++)
  {
    Serial.print("Testing pin code ");
    Serial.println(pinTests[i]);
    digitalWrite(pinTests[i], 1);
    delay(1500);
    digitalWrite(pinTests[i], 0);
  }
  Serial.println("");
}