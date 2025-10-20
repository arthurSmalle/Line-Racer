// testing with the arduino nano gyroscope sensors
#ifdef ARDUINO_NANO
#ifndef BMI270_BMM150_TEST_H
#define BMI270_BMM150_TEST_H
#include "Arduino_BMI270_BMM150.h"

class BMI270BMM150Test{
  public:
    bool check_succes(){return this->succesful_init;}
   BMI270BMM150Test(){
     succesful_init= IMU.begin();
   }
  private:
   bool succesful_init = false;
};

#endif
#endif
