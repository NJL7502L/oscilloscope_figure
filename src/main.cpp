#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  analogWriteFrequency(10,234375);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(10, 256*((millis() % 100)/100.0f));
  
}