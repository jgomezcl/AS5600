/**
 * @file ReadAngle.ino
 * @brief Read angle example
 * @details Example showing how to use the AS5600 driver.
 * @author: Joan Gomez
 */

#include <AS5600.h>

AS5600 as5600;

void setup()
{
  /* Start serial port to log data */
  Serial.begin(115200);
}

void loop()
{
  if (as5600.getStatus() == AS5600::STATUS_OK)
  {
    /* Print angle readings in degrees if the status is correct */
    Serial.println(as5600.getDegrees());
  }
  else
  {
    Serial.println("Sensor data unavailable");
    delay(450);
  }
  delay(50);
}
