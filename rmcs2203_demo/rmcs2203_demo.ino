/*

Arduino Code for running RMCS-220X Encoder DC Servo Motors.
RMCS-220X series motors are high torque DC motors with inbuilt encoder and drive. They can be easily controlled by using any MCU such as Arduino or raspberry pi. 
These motors can be controlled through UART, I2C or PPM (Servo signal) and Analog Input (potentiometer control) which makes it versatile servo motor.
Encoder is inbuilt so perfect speed control can be achieved. Shaft stays locked when no command is given.
This code uses I2C interface to control the motors.
If more than one motor is to be controlled use I2C interface, make sure that every motor has different address. Address can only be set from UART interface.



Connections
---------------
+12 to 15VDC (Min 5A is recommended) - Motor Green, Arduino VIN
GND of power supply- Motor Black, Arduino GND
+5V from Arduino - Motor Yellow, Motor Orange
Pull Up with 10K resistor to +5 - Arduino A4, A5 pins
Arduino A4 - SDA-Motor Red
Arduino A5 - SCL-Motor Brown

*/

#include <Wire.h>
#define dc_servo1 8
#define led 13

long CurPos;

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
    Serial.begin(9600);    //Initiate serial port
  while (!Serial) {      //For leonardo only - wait for connection
  }
  SetMaxSpeed(dc_servo1,255);
  SetDamping(dc_servo1,0);
  SpeedRun(dc_servo1,0);
  Serial.println("Motor Stopped");
  delay(1000);  
  pinMode(led, OUTPUT);    //Setup LED pin as output
  digitalWrite(led, 1);    //LED On
}



void loop()
{
Demo();
}

void SpeedRun(byte Address, int Speed)
{
  Wire.beginTransmission(Address);
  Wire.write(1);
  Wire.write(Speed         & 0xff);
  Wire.write((Speed >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}

void SetMaxSpeed(byte Address, byte Speed)
{
  Wire.beginTransmission(Address);
  Wire.write(0);
  Wire.write(Speed);
  Wire.write(0);
  Wire.endTransmission();
}

void SetDamping(byte Address, byte Damping)
{
  Wire.beginTransmission(Address);
  Wire.write(2);
  Wire.write(Damping);
  Wire.write(0);
  Wire.endTransmission();
  delay(50);    //Required to store settings
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

void MoveRel(byte Address, long Position)
{
  Wire.beginTransmission(Address);
  Wire.write(8);
  Wire.write(Position         & 0xff);
  Wire.write((Position >>  8) & 0xff);
  Wire.write((Position >> 16) & 0xff);
  Wire.write((Position >> 24) & 0xff);
  Wire.endTransmission();
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

long ReadPos(void)
{
  
}

void Demo(void)
{
//---------Speed Mode tesing
  Serial.println("Speed Control Mode");
  int i;
  SetDamping(dc_servo1,100);  
  Serial.println("Motor Running at Speed -255 Damping 100");
  SpeedRun(dc_servo1,-255);
  delay(3000);
  digitalWrite(led, 0);
  Serial.println("Motor Running at Speed -255 Damping 100");
  SetDamping(dc_servo1,0);  
  for(i=-255;i<=255;i++)
  {
    SpeedRun(dc_servo1,i);
    Serial.println(i);
    delay(30);
  }
  digitalWrite(led, 1);
  SetDamping(dc_servo1,200);  
  SpeedRun(dc_servo1,0);
  Serial.println("Motor Running at Speed 0 Damping 200");
  delay(3000);
  digitalWrite(led, 0);
  SetDamping(dc_servo1,0);  
//----------Position Mode testing

  Serial.println("Position Mode, Set current position to 0");
  SetPos(dc_servo1,0);
  delay(3000);
  digitalWrite(led, 1);    //LED On
  Serial.println("Position Mode, Move half rotaiton : 900 steps");
  MoveAbs(dc_servo1, 900);
  delay(3000);
  Serial.println("Position Mode, Go to 0 Position");
  MoveAbs(dc_servo1, 0);
  delay(3000);
  Serial.println("Position Mode Relative Move, Go to +2000 Counts");
  MoveRel(dc_servo1, 2000);
  delay(500);
  Serial.println("Position Mode Relative Move, Go to +1000 Counts");
  MoveRel(dc_servo1, 1000);
  delay(500);
  Serial.println("Position Mode Relative Move, Go to +500 Counts");
  MoveRel(dc_servo1, 500);
  delay(500);
  Serial.println("Position Mode Relative Move, Go to -200 Counts");
  MoveRel(dc_servo1, -200);
  delay(500);
  Serial.println("Position Mode Absolute Move, Go to 0 Position");
  MoveAbs(dc_servo1, 0);
  Serial.println("End Program, Strating over...");
  delay(3000);
  digitalWrite(led, 0);
}

