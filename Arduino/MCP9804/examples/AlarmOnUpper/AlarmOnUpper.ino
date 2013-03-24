//
// AlarmOnUpper.ino - Example program configuring the alarm on an upper temperature.
//
// Created by Christophe Augier <christophe.augier@gmail.com>, March 2013.
//
// This work is licensed under a Creative Commons Attribution-ShareAlike
// 3.0 Unported License (http://creativecommons.org/licenses/by-sa/3.0/deed.en_US)

// The component is configured by default with address 0x1f which means that
// A1, A2 and A3 are all connected to Vcc.
//
// The I2C cables are connected to A4 and A5.

#include <Wire.h>
#include <MCP9804.h>

MCP9804 sensor(0x1f); // default address 0x1f

void setup()
{
  Serial.begin(9600);

  sensor.setResolution(MCP9804::R_0_25);
  sensor.setTUpper(temp_to_val(30.5));
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
}

