#include <Wire.h>

#define dc_servo1 16
#define dc_servo2 8

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A0,INPUT);
  Wire.begin();
  SetPos(dc_servo1,0);
  SetPos(dc_servo2,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int xVal = avgSensorVal(A0,20);
  int yVal = avgSensorVal(A1,20);
  int rollerVal = avgSensorVal(A2,20);
  long servo1Pos = map(xVal,512,1023,0,1800);
  long servo2Pos = map(rollerVal,512,1023,0,1800);
  MoveAbs(dc_servo1,servo1Pos);
  MoveAbs(dc_servo2,servo2Pos);
  
  
}

long ReadPos(int Address)
{
  Wire.beginTransmission(Address + 0); // send the slave address of the RMCS-220x and write bit 0 
  Wire.write(3); //Command for position
  Wire.endTransmission();
  /*
  Wire.beginTransmission(Address + 1); // send I2C address with repeated start and 1 to read 
  
  byte posMSB = I2C_Read_Ack(); // read speed LSB byte and ack 
  
  byte posLSB = I2C_Read_Nak(); // read speed MSB byte and don’t ack
  */
  Wire.requestFrom(Address,4);
  byte pos0 = Wire.read();
  byte pos1 = Wire.read();
  byte pos2 = Wire.read();
  byte pos3 = Wire.read();
  Wire.endTransmission(); // send I2C stop
  
  return (pos3<<24) | (pos2 << 16) | (pos1 << 8) | pos0;
}

void SetPos(byte Address, long Position)
{
  Wire.beginTransmission(Address);
  Wire.write(3);
  Wire.write(Position         & 0xff);
  Wire.write((Position >>  8) & 0xff);
  Wire.write((Position >> 16) & 0xff);
  Wire.write((Position >> 24) & 0xff);
  Wire.endTransmission();
}

void SpeedRun(byte Address, int Speed)
{
  Wire.beginTransmission(Address);
  Wire.write(1);
  Wire.write(Speed         & 0xff);
  Wire.write((Speed >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}

void MoveAbs(byte Address, long Position)
{
  Wire.beginTransmission(Address);
  Wire.write(4);
  Wire.write(Position         & 0xff);
  Wire.write((Position >>  8) & 0xff);
  Wire.write((Position >> 16) & 0xff);
  Wire.write((Position >> 24) & 0xff);
  Wire.endTransmission();
}

int avgSensorVal(int pin, int nSamples){
  long sum = 0;
  for (int i=0; i<nSamples; i++){
    sum += analogRead(pin);
  }
  return (sum / nSamples);
}
