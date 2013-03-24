//
// mcp9804.cpp - Library for MCP9804 digital temperature sensor
//
// Created by Christophe Augier <christophe.augier@gmail.com>, March 2013.
//
// This work is licensed under a Creative Commons Attribution-ShareAlike
// 3.0 Unported License (http://creativecommons.org/licenses/by-sa/3.0/deed.en_US)

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

#include "MCP9804.h"
#include <Wire.h>

MCP9804::MCP9804(int address)
{
    _address = address;
    Wire.begin();
}

#define ERROR_CODE 0xffff

unsigned int MCP9804::readRegister(Register reg)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(_address, 2 /*bytes*/);
  int value;
  if (Wire.available()) {
    value = Wire.read();
    value <<= 8;
  } else {
    return ERROR_CODE;
  }
  if (Wire.available()) {
    value |= Wire.read();
  } else {
    return ERROR_CODE;
  }
  return value;
}

void MCP9804::setResolution(TemperatureResolution res)
{
  Wire.beginTransmission(_address);
  Wire.write(MCP9804::Resolution);
  Wire.write(res);
  Wire.endTransmission();
}

void MCP9804::setTLimit(Register reg, int temp)
{
  Wire.beginTransmission(_address);
  Wire.write(reg);
  Wire.write((byte) (temp >> 8));
  Wire.write((byte) (temp & 0xff));
  Wire.endTransmission();
}

void MCP9804::setTLower(int temp)
{
  setTLimit(MCP9804::TLower, temp);
}

void MCP9804::setTUpper(int temp)
{
  setTLimit(MCP9804::TUpper, temp);
}

void MCP9804::setTCrit(int temp)
{
  setTLimit(MCP9804::TCritical, temp);
}

unsigned int MCP9804::readTemperature()
{
    return readRegister(MCP9804::TAmbient);
}

unsigned int MCP9804::getDeviceRevisionID()
{
    return readRegister(MCP9804::DeviceRevision);
}

unsigned int MCP9804::getManufacturerID()
{
    return readRegister(MCP9804::Manufacturer);
}

/*
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
*/
