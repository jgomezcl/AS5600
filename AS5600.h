/****************************************************
  AS5600 class for Arduino-compatible boards
  Author: Joan Gomez
  Date: 25 May 2021
  File: AS5600.h
  Version 1.00

  Description:  This class has been designed to
  access the chinese breakout board of the AS5600S.
  Adapted from the SeedStudio library for its Groove
  AS5600 Magnetic Rotary Position Encoder.
  https://github.com/Seeed-Studio/Seeed_Arduino_AS5600

  *****************************************************/
#ifndef AS5600_h
#define AS5600_h

#include <Arduino.h>

class AS5600
{
  public:
    AS5600(void);
    uint8_t getAddress();
    uint16_t getRawAngle();
    float getAngle();
    uint8_t getMagnetStatus();

  private:
    uint8_t readOneByte(int in_adr);
    uint16_t readTwoBytes(int in_adr_hi, int in_adr_lo);

    int _as5600_address;
    int _stat;
    int  _raw_ang_hi;
    int _raw_ang_lo;
};

#endif
