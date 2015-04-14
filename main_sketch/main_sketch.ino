#include <Wire.h>

#include "RMCS2203.h"

RMCS2203 baseRotate;
RMCS2203 baseJoint;

void setup() {
  Wire.begin();
  baseRotate.attach(16);
  baseJoint.attach(8);
  pinMode(A0,INPUT);
  baseRotate.calibrate();
  baseJoint.calibrate();
  baseRotate.calibrateZeroPosition();
  baseJoint.calibrateZeroPosition();
}

void loop() {
  int xVal = avgSensorVal(A0,20);
  int yVal = avgSensorVal(A1,20);
  int rollerVal = avgSensorVal(A2,20);
  long servo1Pos = map(xVal,512,1023,0,900);
  long servo2Pos = map(yVal,512,1023,0,900);
  baseRotate.goToAbsPosition(servo1Pos);
  baseJoint.goToAbsPosition(servo2Pos);
  
}

int avgSensorVal(int pin, int nSamples){
  long sum = 0;
  for (int i=0; i<nSamples; i++){
    sum += analogRead(pin);
  }
  return (sum / nSamples);
}
