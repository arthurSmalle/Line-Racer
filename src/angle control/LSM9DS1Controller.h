#ifndef LSM9DS1CONTROLLER_H
#define LSM9DS1CONTROLLER_H
#include "MagMeterController.h"
class LSM9DS1Controller : MagMeterController{
  public:
    LSM9DS1Controller(){}
    float get_angle_to_zero() override;
    int get_mag_data(float &x,float &y,float &z) override;
    bool is_mag_ready() override;
    void set_angle_to_magdata_ref() override;
  protected:
    void get_zero_point() override; // calibrate the zero point of the magnetometer
};
#endif
