/*
  Using the ZOPT220x UV Sensor
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 4th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  This example shows how to change I2C address between 0x52 and 0x53 (default)

  The ZOPT2201 sensor detects UVB + Ambient Light Sensor (ALS)
  The ZOPT2202 sensor detects UVA + UVB

  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the ZOPT220x onto the shield
  Serial.print it out at 115200 baud to serial monitor.

  Available:
  enableALSSensing() //ALS + COMP channels activated
  enableUVBSensing() //UVB + UV_COMP channels activated
  enableRawSensing() //ALS and UVB but no temperature compensation
  long getUVB()
  long getALS()
  setMeasurementRate(byte) 0 to 7
  setResolution(byte) 0 to 5
  setGain(byte) 0 to 4
  enableSensor()
  disableSensor()
  dataAvailable()
  checkPowerOnStatus()
  softReset()
  setI2CAdr52() //Set I2C address to 0x52
  setI2CAdr53() //Set I2C address to 0x53

*/

#include <Wire.h>

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Serial.println("ZOPT220x Change I2C Example");

  Wire.begin();

  if (zopt220xSetupWithAddress(0x53) == true) //Default address
  {
    Serial.println("Sensor found at default 0x53.");
    
    //The ZOPT2201 default I2C address is 0x53. To change it to 0x52:  
    setI2CAdr52();

    Serial.println("Address changed. Reset board to connect at new address.");
    while(1); //Freeze
  }
  else if (zopt220xSetupWithAddress(0x52) == true) //Changed address
  {
    Serial.println("Sensor found at changed address 0x52.");
  }
  else
  {
    Serial.println("No sensor found. Check wiring.");
    while(1); //Freeze
  }
}

void loop()
{
  if (dataAvailable())
  {
    long uvb = getUVB();
    Serial.print("UVB: ");
    Serial.println(uvb);
  }

  delay(1);
}
