// class to drive the motors (only to drive the  motors not to adjust the angle of the robot directly)
#ifndef  L298NCONTROLLER_H
#include <Arduino.h>

class L298NController{
  public:
    bool clockwise = true; // default is clockwise, toggle to false to set anti-clockwise
    bool en_hard_stop = false; // if the throttle is set to 0, enable hard stop instead of just cutting the power

    float throttle_limiter = 100;
    
    // implement setter and getter functions for the values
    void set_throttle(const float throttle);

    L298NController(const uint8_t motor_pin_1, const uint8_t motor_pin_2){
      this->motor_pin_1 = motor_pin_1;
      this->motor_pin_2 = motor_pin_2;
    }

  private:
    uint8_t motor_pin_1;
    uint8_t motor_pin_2;
};

#endif
