/**
 * @file AS5600.h
 * @brief AS5600 driver for Arduino-compatible boards
 * @details This library has been created to handle the chinese breakout board
 * for the AS5600S magnetic absolute encoder via I2C.
 * @author: Joan Gomez
 * @version 1.1
 */

#ifndef AS5600_h
#define AS5600_h

#include <Arduino.h>

class AS5600
{
    public:
        /* Sensor status */
        typedef enum
        {
            STATUS_OK = 0U,             /* Status is ok */
            STATUS_MAGNET_CLOSE,        /* Magnet is too close */
            STATUS_MAGNET_FAR,          /* Magnet is too far */
            STATUS_NO_MAGNET            /* No magnet detected */
        } EStatus;

        /**
         * Initializes the sensor.
         */
        AS5600(void);

        /**
         * Provides the current status of the sensor.
         *
         * @retval Sensor status (see EStatus)
         */
        EStatus
        getStatus(void);

        /**
         * Provides the current angle in counts.
         *
         * @retval Angle in counts (12 bit/rev)
         */
        uint16_t
        getCounts(void);

        /**
         * Provides the current angle in degrees.
         *
         * @retval Angle in degrees
         */
        float
        getDegrees(void);

    private:
        /**
         * Reads data from one or several consecutive registers.
         *
         * @param[in] u8Addr
         *  Register address
         * @param[out] pu8Dst
         *  Destinatin were read data will be stored
         * @param[in] u8Size
         *  Size in bytes of the data to be read
         *
         * @retval Number of read bytes
         */
        uint8_t
        read(uint8_t u8Addr,
             uint8_t* pu8Dst,
             uint8_t u8Size);
};

#endif
