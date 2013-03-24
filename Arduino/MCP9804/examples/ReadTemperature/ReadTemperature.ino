//
// ReadTemperature.ino - Example program reading and printing the temperature
//
// Created by Christophe Augier <christophe.augier@gmail.com>, March 2013.
//
// This work is licensed under a Creative Commons Attribution-ShareAlike
// 3.0 Unported License (http://creativecommons.org/licenses/by-sa/3.0/deed.en_US)

#include <Wire.h>
#include <MCP9804.h>

MCP9804 sensor(0x1f);

void setup()
{
  Serial.begin(9600);

  // Set Digital sensor resolution to the maximum: 0.0625 degrees
  //
  sensor.setResolution(MCP9804::R_0_0625);
}

int temp_to_val(float temp)
{
  int neg = temp < 0 ? 1 : 0;
  if (neg) {
    temp = -temp;
  }
  int tmp = (int) (temp * 16);
  tmp = (tmp & 0x3ff) | (neg << 11);
  return tmp;
}

float val_to_temp(int val)
{
  float temp = (val & 0x3ff) / 16.0;
  if (val & 0x800) {
    temp *= -1;
  }
  return temp; 
}

void loop()
{
  Serial.print(val_to_temp(sensor.readTemperature()));
  Serial.println(" degrees");
  delay(1000);
/*
  Serial.print(sensor.getManufacturerID());
  Serial.print(' ');

  Serial.print(sensor.getDeviceRevisionID());
  Serial.print(' ');

  sensor.setTLower(temp_to_val(-10.5));
  sensor.setTUpper(temp_to_val(30.5));
  sensor.setTCrit(temp_to_val(30.5));
*/
}

