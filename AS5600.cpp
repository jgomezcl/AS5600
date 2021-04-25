/****************************************************
  AS5600 class for Arduino-compatible boards
  Author: Joan Gomez
  Date: 25 May 2021
  File: AS5600.cpp
  Version 1.00

  Description:  This class has been designed to
  access the chinese breakout board of the AS5600S.
  Adapted from the SeedStudio library for its Groove
  AS5600 Magnetic Rotary Position Encoder.
  https://github.com/Seeed-Studio/Seeed_Arduino_AS5600

  *****************************************************/

#include "Arduino.h"
#include "Wire.h"
#include "AS5600.h"


AS5600::AS5600()
{
  _as5600_address = 0x36;
  _stat = 0x0b;
  _raw_ang_hi = 0x0c;
  _raw_ang_lo = 0x0d;

  Wire.begin();
}

uint8_t AS5600::getAddress()
{
  return _as5600_address;
}

uint8_t AS5600::getMagnetStatus()
{
  uint8_t magStatus;

  //0 0 MD ML MH 0 0 0
  //MD high > magnet detected
  //ML high > magnet too weak
  //MH high > Magnet too strong
  magStatus = readOneByte(_stat);

  if (magStatus & 0x20)
    return 1;   //magnet ok

  if (magStatus & 0x08)
    return 2;   //too strong

  return 0;     //too weak or not present
}

uint16_t AS5600::getRawAngle()
{
  return readTwoBytes(_raw_ang_hi, _raw_ang_lo);
}

float AS5600::getAngle()
{
  uint16_t angle = readTwoBytes(_raw_ang_hi, _raw_ang_lo);
  return angle * 0.08789;   //conversion from 0-4095 to 0-360
}

uint8_t AS5600::readOneByte(int in_adr)
{
  uint8_t retVal = -1;
  Wire.beginTransmission(_as5600_address);
  Wire.write(in_adr);
  Wire.endTransmission();
  Wire.requestFrom(_as5600_address, 1);
  while (Wire.available() == 0)
    ;
  retVal = Wire.read();

  return retVal;
}

uint16_t AS5600::readTwoBytes(int in_adr_hi, int in_adr_lo)
{
  uint16_t retVal;

  //Read the low byte
  Wire.beginTransmission(_as5600_address);
  Wire.write(in_adr_lo);
  Wire.endTransmission();
  Wire.requestFrom(_as5600_address, 1);
  while (Wire.available() == 0)
    ;
  uint8_t low = Wire.read();

  //Read the high byte
  Wire.beginTransmission(_as5600_address);
  Wire.write(in_adr_hi);
  Wire.endTransmission();
  Wire.requestFrom(_as5600_address, 1);

  while (Wire.available() == 0)
    ;

  retVal = Wire.read();

  //Join both values
  retVal = retVal << 8;
  retVal = retVal | low;

  return retVal;
}
