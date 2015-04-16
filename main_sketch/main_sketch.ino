
#include <Wire.h>
#include <Servo.h> 
#include "RMCS2203.h"

RMCS2203 baseRotate;
RMCS2203 baseJoint;
Servo gripJoint;

// 1023 <-- wheel ->> ~540
int prevRollerVal = 1023;
void setup() {
  Wire.begin();
  
  //Serial.begin(9600);
  
  baseRotate.attach(16);
  baseJoint.attach(8);
  gripJoint.writeMicroseconds(1500);
  gripJoint.attach(9);
  pinMode(A0,INPUT);
  baseRotate.defaultGains();
  baseJoint.defaultGains();
  baseJoint.setMaxSpeed(255);
  baseRotate.setMaxSpeed(255);
  baseRotate.calibrateZeroPosition();
  baseJoint.calibrateZeroPosition();
}


void loop() {
  int xVal = avgSensorVal(A0,30);
  int yVal = avgSensorVal(A1,30);;
  int rollerVal = avgSensorVal(A2,200);
  rollerVal = smoothSensorVal(rollerVal, prevRollerVal); 
  prevRollerVal = rollerVal;
 
  long servo1Pos = map(xVal,512,1023,0,900);
  long servo2Pos = map(yVal,512,1023,0,900);
  long servo3Pos = map(rollerVal,540,1023,1000,2000);
  baseRotate.goToAbsPosition(servo1Pos);
  baseJoint.goToAbsPosition(servo2Pos);
  gripJoint.writeMicroseconds(servo3Pos);
  
//  Serial.println(rollerVal);
//  delay(500);
}
// average incoming sensor values
int avgSensorVal(int pin, int nSamples){
  long sum = 0;
  for (int i=0; i<nSamples; i++){
    sum += analogRead(pin);
  }
  return (sum / nSamples);
}
//Smooth incoming rollerwheel values because 
//of variability in sensor reads
int smoothSensorVal(int val, int prevVal){
  if (abs(prevVal - val) > 25){
    return val;
  }
  else return prevVal;
}
