/*
  Using the ZOPT2201 and ZOPT2202 UV Sensor
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 4th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  This example outputs the current UV Index (1 to 11+).

  The ZOPT2201 sensor detects UVB + Ambient Light Sensor (ALS)
  The ZOPT2202 sensor detects UVA + UVB

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
  Serial.println("ZOPT220x UV Index Example");

  Wire.begin();

  if (zopt220xSetup() == false)
  {
    Serial.println("Sensor failed to respond. Check wiring.");
    while (1); //Freeze!
  }
  Serial.println("ZOPT220x online!");

  enableUVBSensing(); //UVB + UV_COMP channels activated
}

void loop()
{
  float uvIndex = getUVIndex();

  Serial.print("UV Index: ");
  Serial.println(uvIndex);

  if (uvIndex > 8)
    Serial.println("Put on sun screen!");

  delay(1000);
}
