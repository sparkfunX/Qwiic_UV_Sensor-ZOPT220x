/*
  Using the ZOPT220x UV Sensor
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 4th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Quickly check to see if sensor responds and check ambient light level.
  
  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the ZOPT220x onto the shield
  Serial.print it out at 115200 baud to serial monitor.
*/

#include <Wire.h>

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("ZOPT220x Read Example");

  Wire.begin();

  enableMuxPort(0); //Tell mux to connect to port 0
}

void loop()
{
  if (zopt220xSetup() == false)
  {
    Serial.println("Sensor failed to respond.");
  }
  else
  {
    setResolution(2); //18 bit, 100ms, default
    enableALSSensing();

    while(!dataAvailable()) delay(1); //Wait for reading to complete

    long als = getALS();
    Serial.print("ZOPT220x online!");
    Serial.print(" ALS: ");
    Serial.println(als);
  }

  delay(1);
}
