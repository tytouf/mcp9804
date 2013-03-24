//
// MCP9804.h - Library for MCP9804 digital temperature sensor
//
// Created by Christophe Augier <christophe.augier@gmail.com>, March 2013.
//
// This work is licensed under a Creative Commons Attribution-ShareAlike
// 3.0 Unported License (http://creativecommons.org/licenses/by-sa/3.0/deed.en_US)

#ifndef MCP9804_H
# define MCP9804_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

#include <Wire.h>

class MCP9804
{
  private:
    int _address;

  public:
    enum Register {
        RFU = 0x0,
        Config = 0x1,
        TUpper = 0x2,
        TLower = 0x3,
        TCritical = 0x4,
        TAmbient = 0x5,
        Manufacturer = 0x6,
        DeviceRevision = 0x7,
        Resolution = 0x8
    };

    enum TemperatureResolution {
        R_0_5 = 0,
        R_0_25 = 1,
        R_0_125 = 2,
        R_0_0625 = 3
    };

    MCP9804(int address);
    unsigned int readTemperature();
    void setResolution(TemperatureResolution res);
    void setTLower(int temp);
    void setTUpper(int temp);
    void setTCrit(int temp);
    unsigned int getDeviceRevisionID();
    unsigned int getManufacturerID();
    unsigned int readRegister(Register reg);

  private:
    void setTLimit(Register reg, int temp);
};

#endif // MCP9804_H
