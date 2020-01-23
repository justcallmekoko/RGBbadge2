#ifndef Battery_h
#define Battery_h

#define IP5306_ADDR 0x75
#define IP5306_CHECK_INTERVAL 10

#include <Wire.h>

class Battery
{
  private:

  public:
    Battery();

    bool ip5306_i2c_capable = false;
    
    int8_t current_level = -1;

    bool checkIP5306I2C();
    int8_t getBatteryLevel();
};

#endif
