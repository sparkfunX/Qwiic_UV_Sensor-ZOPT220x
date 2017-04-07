
//Given location and time, calculation current elevation of sun
//From App note "UV Index Calculation" from IDT
//This is extremely experimental and questionable
//Is the fourth term of equation 6 [0.014615 * cos(2 * n)] supposed to be negative? Seems like it should be +.
float getElevationAdjustedUVIndex(float longitude, float latitude, int day, byte hour, byte minute)
{
  long startTime = millis(); //Let's time how long this calculation takes
  
  float k = 3.14159 / 180.0; //Constant
  
  //Equation 4 - Fractional year calculation (in radians)
  float n;
  n = day - 1.0;
  n += (((hour + 1.0 + (minute / 60.0)) - 12) / 24.0);
  n *= 2 * 3.14159 / 365;

  //Equation 5 - Declination angle in radians
  float declin;
  declin = 0.006918 - 0.399912 * cos(n);
  declin += 0.070257 * sin(n);
  declin -= 0.006758 * cos(n);
  declin += 0.000907 * sin(n);
  declin -= 0.002697 * cos(3.0 * n / 2.0);
  declin += 0.00148 * sin(3.0 * n / 2.0);

  //Equation 6 - Equation of time
  float t;
  t = 0.000075;
  t += 0.001868 * cos(n);
  t -= 0.032077 * sin(n);
  t -= 0.014615 * cos(2 * n);
  t -= 0.040849 * sin(2 * n);
  t *= 229.18;

  //Equation 7 - Hour angle in degrees
  float a;
  a = hour + 1.0;
  a += minute / 60.0;
  a -= ((15 - longitude) / 15.0);
  a -= 12.0;
  a += (t / 60.0);
  a *= 15.0;
  
  //Equation 8 - Sine of elevation angle
  float x;
  x = sin(k * latitude) * sin(declin);
  x += cos(k * latitude) * cos(declin) * cos(k * a);
  
  //Equation 9
  float elevation;
  elevation = 1.0 / k;
  elevation *= asin(x);

  //Elevation calculated!

  //Equation 3 - Calculation the UVI Correction value
  float c0 = 3.1543;
  float c1 = -0.06204;
  float c2 = 0.0002186;
  float c3 = 0.0000035516;
  
  float uviCorrection;
  uviCorrection = c0 * pow(elevation, 0);
  uviCorrection += c1 * pow(elevation, 1);
  uviCorrection += c2 * pow(elevation, 2);
  uviCorrection += c3 * pow(elevation, 3);

  long stopTime = millis();

  Serial.print("n: ");
  Serial.println(n);
  Serial.print("declin: ");
  Serial.println(declin, 3);
  Serial.print("t: ");
  Serial.println(t, 3);
  Serial.print("a: ");
  Serial.println(a, 3);
  Serial.print("x: ");
  Serial.println(x, 3);
  Serial.print("elevation: ");
  Serial.println(elevation, 3);
  Serial.print("uviCorrection: ");
  Serial.println(uviCorrection, 3);
  Serial.print("calc time: ");
  Serial.println(stopTime - startTime);
  
  //Get current UBV reading
  byte counter = 0;
  while(!dataAvailable())
  {
    delay(10);
    if(counter++ > 50) //We should have a reading in 400ms
    {
      //We've timed out waiting for the data. Return error
      return(-1.0);
    }
  }
  long uvb = getUVB(); //Get new data

  float uvIndex = getAdjustedUVIndex(uvb, 4, 0, uviCorrection); //Assumes default for UVI of gain:4, resolution:0, uviCorrection of 1.0
  return(uvIndex);
}

