#include <Wire.h>
#define dc_servo1 16
#define dc_servo2 8
#define led 13

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=-255;i<=255;i++)
  {
    SpeedRun(dc_servo1,i);
    SpeedRun(dc_servo2,-i/2);
    Serial.println(i);
    Serial.print("Read from servo 2: ");
    Serial.println(ReadPos(dc_servo2));
    Serial.println();
    delay(50);
  }
  SpeedRun(dc_servo1,0);
  SpeedRun(dc_servo2,0);
  delay(10000);
}

void SpeedRun(byte Address, int Speed)
{
  Wire.beginTransmission(Address);
  Wire.write(1);
  Wire.write(Speed         & 0xff);
  Wire.write((Speed >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
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
