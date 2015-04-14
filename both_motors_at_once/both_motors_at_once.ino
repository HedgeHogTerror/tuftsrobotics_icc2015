#include <Wire.h>
#define dc_servo1 16
#define dc_servo2 8
#define led 13

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); // join i2c bus (address optional for master)

}

void loop() {`2``
  // put your main code here, to run repeatedly:
  for(int i=-255;i<=255;i++)
  {
    SpeedRun(dc_servo1,i);
    SpeedRun(dc_servo2,-i/2);
    Serial.println(i);
    delay(30);
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
