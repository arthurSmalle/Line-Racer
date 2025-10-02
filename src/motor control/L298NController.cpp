#include "L298NController.h"

    void L298NController::set_throttle(const float throttle){
      // check if the throttle is set to 0 (evade all other logic)
      if (throttle == 0.0){
	if (this->en_hard_stop){
	  analogWrite(this->motor_pin_1 , 255);
	  analogWrite(this->motor_pin_2 , 255);
	} else{
	  analogWrite(this->motor_pin_1 , 0);
	  analogWrite(this->motor_pin_2 , 0);
	}
	return;
      }

      // pwm in the arduino standard lib is expressed in values from 0 to 255 => conversion is needed if working with %
      int actual_throttle = int((255 / this->throttle_limiter) * throttle);
      if (this->clockwise){
	analogWrite(this->motor_pin_1 , actual_throttle);
	analogWrite(this->motor_pin_2, 0);
      } else {
	analogWrite(this->motor_pin_1 , 0);
	analogWrite(this->motor_pin_2, actual_throttle);
      }
    }
