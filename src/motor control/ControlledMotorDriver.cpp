#include "ControlledMotorDriver.h"
#include <Arduino.h>

void ControlledMotorDriver::update(){
  tachometer.calculate_rpm();
  this->rpm = tachometer.get_rpm();

  this->error_signal = this->set_point - this->rpm;

  pid.set_error_signal(this->error_signal);
  pid.calculate_output();

  float pid_output = pid.get_output_signal();
  
  physical_driver.set_throttle(pid_output);
}
