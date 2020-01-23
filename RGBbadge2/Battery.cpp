#include "Battery.h"

Battery::Battery()
{
  Wire.begin();
}

bool Battery::checkIP5306I2C()
{
  Wire.beginTransmission(IP5306_ADDR);
  if (Wire.endTransmission() == 0)
  {
    this->ip5306_i2c_capable = true;
    return true;
  }
  return false;
}

int8_t Battery::getBatteryLevel()
{
  Wire.beginTransmission(IP5306_ADDR);
  Wire.write(0x78);
  if (Wire.endTransmission(false) == 0 &&
      Wire.requestFrom(0x75, 1)) {
    switch (Wire.read() & 0xF0) {
      case 0xE0: return 25;
      case 0xC0: return 50;
      case 0x80: return 75;
      case 0x00: return 100;
      default: return 0;
    }
  }
  return -1;
}
