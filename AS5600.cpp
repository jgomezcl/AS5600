/**
 * @file AS5600.c
 */

#include "Arduino.h"
#include "Wire.h"
#include "AS5600.h"

#define I2C_ADDR        0x36U           /* I2C address */

/* Registers */
#define REG_STATUS      0x0BU           /* Sensor status register */
#define REG_RAW_ANG_HI  0x0CU           /* Raw angle (MSB) register */
#define REG_RAW_ANG_LO  0x0DU           /* Raw angle (LSB) register */

/* Sensor status flags */
#define STATUS_MH       0x08U           /* AGC minimum gain overflow, magnet too strong */
#define STATUS_ML       0x10U           /* AGC maximum gain overflow, magnet too weak */
#define STATUS_MD       0x20U           /* Magnet detected */

#define CNT_TO_DEG      (360.0/4096.0)  /* Conversion factor from counts to degrees */

AS5600::AS5600(void)
{
    Wire.begin();
}

AS5600::EStatus AS5600::getStatus(void)
{
    uint8_t u8Status;
    EStatus eRet;

    this->read(REG_STATUS, &u8Status, 1U);

    if ((u8Status & STATUS_MH) != 0U)
    {
        eRet = STATUS_MAGNET_CLOSE;
    }
    else if ((u8Status & STATUS_ML) != 0U)
    {
        eRet = STATUS_MAGNET_FAR;
    }
    else if ((u8Status & STATUS_MD) == 0U)
    {
        eRet = STATUS_NO_MAGNET;
    }
    else
    {
        eRet = STATUS_OK;
    }
    return eRet;
}

uint16_t AS5600::getCounts(void)
{
    uint16_t u16Cnt;
    this->read(REG_RAW_ANG_HI, (uint8_t*)&u16Cnt, 2U);
    /* Swap bytes */
    return ((u16Cnt & 0x000FU) << 8) | ((u16Cnt & 0xFF00U) >> 8);
}

float AS5600::getDegrees(void)
{
    uint16_t u16Cnt = this->getCounts();
    return ((float)u16Cnt) * CNT_TO_DEG;
}

uint8_t AS5600::read(uint8_t u8Addr, uint8_t* pu8Dst, uint8_t u8Size)
{
    for (uint8_t u8Bytes = 0U; u8Bytes < u8Size; u8Bytes++)
    {
        Wire.beginTransmission((uint8_t)I2C_ADDR);
        Wire.write(u8Addr + u8Bytes);
        Wire.endTransmission();
        Wire.requestFrom((uint8_t)I2C_ADDR, (uint8_t)1U);
        while (Wire.available() == 0)
        {
            /* Wait */
        };
        pu8Dst[u8Bytes] = Wire.read();
    }
}
