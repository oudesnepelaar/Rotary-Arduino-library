#include <RotaryEncoder.h>

RotaryEncoder rotEnc = RotaryEncoder(3, 2, 5);
int resultValue = 0;

void setup() {

  attachInterrupt(digitalPinToInterrupt(3), sampleStatus, CHANGE);
  attachInterrupt(digitalPinToInterrupt(2), sampleStatus, CHANGE);
  
  Serial.begin(19200);
  while (! Serial);
  Serial.println("System initiated...\n");
}

void loop() {
}

void sampleStatus() {
  
  int rotStatus = rotEnc.sampleRotationStatus();
  if (rotStatus != 0) {
    
    resultValue += rotStatus;
    Serial.println(resultValue);
  }
}
