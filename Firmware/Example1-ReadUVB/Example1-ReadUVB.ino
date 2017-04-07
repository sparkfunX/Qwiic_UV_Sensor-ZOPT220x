/*
  Using the ZOPT220x UV Sensor
  By: Nathan Seidle
  SparkFun Electronics
  Date: April 4th, 2017
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Read the UVB readings (temperature compensated).

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

  enableMuxPort(0); //Tell mux to connect to port 0

  if (zopt220xSetup() == false)
  {
    Serial.println("Sensor failed to respond. Check wiring.");
    while (1); //Freeze!
  }
  Serial.println("ZOPT220x online!");

  //enableUVBSensing(); //UVB + UV_COMP channels activated
  enableALSSensing(); //ALS + COMP channels activated
  //enableRawSensing(); //All the channels. No temperature compensation

  //setMeasurementRate(0); //25ms
  //setResolution(5); //13 bit, fast read
  
  //setGain(1); //Default for ALS
  //setGain(4); //Default for UVB
}

void loop()
{
  if (dataAvailable())
  {
    /*byte gain = 3; //4 is what it should be
    byte resolution = 1; //0 for best results but 400ms read time required
    long uvtest = 38756;

    getUVIndex(uvtest, gain, resolution);*/

    //while(1);
    /*Wire.beginTransmission(0x53);
      Wire.write(0x0D);
      Wire.endTransmission();

      Wire.requestFrom(0x53, 12);
      delay(25);
      for (int x = 0 ; x < 12 ; x++)
      {
      Serial.print(x);
      Serial.print("[");
      Serial.print(Wire.read());
      Serial.print("] ");
      }*/

    //long uvb = getUVB();
    //Serial.print("UVB: ");
    //Serial.print(uvb);

    long als = getALS();
    Serial.print(" ALS: ");
    Serial.print(als);

    Serial.println();
  }

  delay(1);
}
