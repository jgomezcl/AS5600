#include <AS5600.h>

AS5600 as5600;

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  if (as5600.getMagnetStatus() > 0)
  {
    Serial.println(as5600.getAngle()); //Print the readings if the magnet is present
  }
  else
  {
    Serial.println("Magnet not found");
    delay(950);   //Extra delay if the magnet is not found
  }
  delay(50);
}
