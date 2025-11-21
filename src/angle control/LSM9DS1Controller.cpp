#include "LSM9DS1Controller.h"
#include <Arduino.h>
#include <Arduino_LSM9DS1.h>

int LSM9DS1Controller::get_mag_data(float &x,float &y,float &z){
  if (IMU.readMagneticField(x, y, z)){
    return 1;
  } else {
    return 0;
  }
}

bool LSM9DS1Controller::is_mag_ready(){
  if (IMU.magneticFieldAvailable()){
    return true;
  } else{
    return false;
  }
}
