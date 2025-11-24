#ifndef LSM9DS1CONTROLLER_H
#define LSM9DS1CONTROLLER_H
#ifdef ARDUINO_NANO_BLE
#include "MagMeterController.h"
class LSM9DS1Controller : public MagMeterController{
  public:
    LSM9DS1Controller(){}
    void update() override;
    int get_mag_data(float &x,float &y,float &z) override;
    bool is_mag_ready() override;
    int init() override;
};
#endif
#endif
