#include "Arduino.h"
#include <Wire.h>
#include "RMCS2203.h"

RMCS2203::RMCS2203(int addr)
{
	address = addr;
}

void RMCS2203::setSpeed(int speed)
{
  Wire.beginTransmission(address);
  Wire.write(1);
  Wire.write(speed         & 0xff);
  Wire.write((speed >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}

int RMCS2203::getSpeed()
{
  Wire.beginTransmission(address + 0); // send the slave address of the RMCS-220x and write bit 0 
  Wire.write(1); //Command for speed
  Wire.endTransmission();
  
  Wire.requestFrom(address,2);
  byte speed0 = Wire.read();
  byte speed1 = Wire.read();
  Wire.endTransmission(); // send I2C stop
  
  return (speed1 << 8) | speed0;
}



void RMCS2203::setMaxSpeed(int maxSpeed)
{
  Wire.beginTransmission(address);
  Wire.write(0);
  Wire.write(maxSpeed         & 0xff);
  Wire.write((maxSpeed >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}

int RMCS2203::getMaxSpeed()
{
  Wire.beginTransmission(address + 0); // send the slave address of the RMCS-220x and write bit 0 
  Wire.write(0); //Command for max speed
  Wire.endTransmission();
  
  Wire.requestFrom(address,2);
  byte maxspeed0 = Wire.read();
  byte maxspeed1 = Wire.read();
  Wire.endTransmission(); // send I2C stop
  
  return (maxspeed1 << 8) | maxspeed0;

}



void RMCS2203::setSpeedDamping(int damping)
{
  Wire.beginTransmission(address);
  Wire.write(2);
  Wire.write(damping         & 0xff);
  Wire.write((damping >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}

int RMCS2203::getSpeedDamping()
{
  Wire.beginTransmission(address + 0); // send the slave address of the RMCS-220x and write bit 0 
  Wire.write(2); //Command for speed damping
  Wire.endTransmission();
  
  Wire.requestFrom(address,2);
  byte val0 = Wire.read();
  byte val1 = Wire.read();
  Wire.endTransmission(); // send I2C stop
  
  return (val1 << 8) | val0;
}



void RMCS2203::setPosition(long pos)
{
  Wire.beginTransmission(address);
  Wire.write(3);
  Wire.write(pos         & 0xff);
  Wire.write((pos >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}

long RMCS2203::getPosition()
{
  Wire.beginTransmission(address + 0); // send the slave address of the RMCS-220x and write bit 0 
  Wire.write(3); //Command for position
  Wire.endTransmission();
  
  Wire.requestFrom(address,4);
  byte pos0 = Wire.read();
  byte pos1 = Wire.read();
  byte pos2 = Wire.read();
  byte pos3 = Wire.read();
  Wire.endTransmission(); // send I2C stop
  
  return (pos3<<24) | (pos2 << 16) | (pos1 << 8) | pos0;
}

void RMCS2203::goToAbsPosition(long absPos)
{
  Wire.beginTransmission(address);
  Wire.write(4);
  Wire.write(absPos         & 0xff);
  Wire.write((absPos >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}

void RMCS2203::goToRelPosition(long relPos)
{
  Wire.beginTransmission(address);
  Wire.write(8);
  Wire.write(relPos         & 0xff);
  Wire.write((relPos >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}



void RMCS2203::setSpeedFeedbackGain(int gain);
{
  Wire.beginTransmission(address);
  Wire.write(5);
  Wire.write(gain         & 0xff);
  Wire.write((gain >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}

int RMCS2203::getSpeedFeedbackGain()
{
  Wire.beginTransmission(address + 0); // send the slave address of the RMCS-220x and write bit 0 
  Wire.write(5); //Command for speed feedback gain
  Wire.endTransmission();
  
  Wire.requestFrom(address,2);
  byte val0 = Wire.read();
  byte val1 = Wire.read();
  Wire.endTransmission(); // send I2C stop
  
  return (val1 << 8) | val0;
}



void RMCS2203::setPGain(int gain)
{
  Wire.beginTransmission(address);
  Wire.write(6);
  Wire.write(gain         & 0xff);
  Wire.write((gain >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}

int RMCS2203::getPGain()
{
  Wire.beginTransmission(address + 0); // send the slave address of the RMCS-220x and write bit 0 
  Wire.write(6); //Command for speed feedback gain
  Wire.endTransmission();
  
  Wire.requestFrom(address,2);
  byte val0 = Wire.read();
  byte val1 = Wire.read();
  Wire.endTransmission(); // send I2C stop
  
  return (val1 << 8) | val0;
}



void RMCS2203::setIGain(int gain)
{
  Wire.beginTransmission(address);
  Wire.write(7);
  Wire.write(gain         & 0xff);
  Wire.write((gain >>  8) & 0xff);
  Wire.endTransmission();    // stop transmitting
}

int RMCS2203::getIGain()
{
  Wire.beginTransmission(address + 0); // send the slave address of the RMCS-220x and write bit 0 
  Wire.write(7); //Command for speed feedback gain
  Wire.endTransmission();
  
  Wire.requestFrom(address,2);
  byte val0 = Wire.read();
  byte val1 = Wire.read();
  Wire.endTransmission(); // send I2C stop
  
  return (val1 << 8) | val0;
}
