#include "L298NController.h"

    void L298NController::set_throttle(const float throttle){
      // check if the throttle is set to 0 (evade all other logic)
      if (throttle == 0.0){
	if (this->en_hard_stop){
	  analogWrite(this->motor_pin_1 , MAX_PWM_VALUE);
	  digitalWrite(this->motor_pin_2 , HIGH);
	} else{
	  analogWrite(this->motor_pin_1 , 0);
	  digitalWrite(this->motor_pin_2 , LOW);
	}
	return;
      }

      // pwm in the arduino standard lib is expressed in values from 0 to 255 => conversion is needed if working with %
      int actual_throttle = int((MAX_PWM_VALUE / this->throttle_limiter) * throttle);

      if (this->clockwise){
	if (actual_throttle > 0){
	  analogWrite(this->motor_pin_1 , abs(actual_throttle));
	  digitalWrite(this->motor_pin_2, LOW);
	} else {
	  analogWrite(this->motor_pin_1 , MAX_PWM_VALUE - abs(actual_throttle));
	  digitalWrite(this->motor_pin_2, HIGH);
	}
      } else {
	if (actual_throttle > 0){
	  analogWrite(this->motor_pin_1 , MAX_PWM_VALUE - abs(actual_throttle));
	  digitalWrite(this->motor_pin_2, HIGH);
	} else {
	  analogWrite(this->motor_pin_1 , abs(actual_throttle));
	  digitalWrite(this->motor_pin_2, LOW);
	}
      }
    }
