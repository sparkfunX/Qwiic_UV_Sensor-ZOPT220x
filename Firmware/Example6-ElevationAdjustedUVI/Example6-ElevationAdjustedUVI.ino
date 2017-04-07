/*
  Using the ZOPT220x UV Sensor
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 4th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  UV is very sensitive to the elevation of the sun.
  Given a lat, long, day, hour, minute, get a very accurate, adjusted UV Index.

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
  Serial.println("ZOPT220x Read Example");

  Wire.begin();

  if (zopt220xSetup() == false)
  {
    Serial.println("Sensor failed to respond. Check wiring.");
    while (1); //Freeze!
  }
  Serial.println("ZOPT220x online!");

  enableUVBSensing(); //UVB + UV_COMP channels activated
}

byte hour = 3 + 12; //3PM
byte minute = 28;

void loop()
{
  if (dataAvailable())
  {
    //April 7th, 2017 3:28PM
    int day = 97; //Jan 01 = 1. From: https://www.epochconverter.com/daynumbers
    hour++;
    minute++;

    //Obtained from google maps. Right click on map -> What's here? gives lat/long of SparkFun HQ
    //Must be in degrees
    float latitude = 40.090579; //N is positive
    float longitude = -105.184831; //W is negative

    float elevationAdjustedUVIndex = getElevationAdjustedUVIndex(latitude, longitude, day, hour, minute);

    Serial.print("Elevation adjusted UV Index: ");
    Serial.print(elevationAdjustedUVIndex);

    long uvb = getUVB();
    Serial.print("UVB: ");
    Serial.print(uvb);

    Serial.println();
  }

  delay(1);
}
