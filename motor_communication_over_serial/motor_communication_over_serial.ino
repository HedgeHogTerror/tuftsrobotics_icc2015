#include <SoftwareSerial.h>

SoftwareSerial motorComm(10,11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  motorComm.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (motorComm.available())
    Serial.write(motorComm.read());
  if (Serial.available())
    motorComm.write(Serial.read());
}
