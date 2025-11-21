#ifndef LSM9DS1CONTROLLER_H
#define LSM9DS1CONTROLLER_H
#include "MagMeterController.h"
class LSM9DS1Controller : MagMeterController{
  public:
    LSM9DS1Controller(){}
    int get_mag_data(float &x,float &y,float &z) override;
    bool is_mag_ready() override;
};
#endif
