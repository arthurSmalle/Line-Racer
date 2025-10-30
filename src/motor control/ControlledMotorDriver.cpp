#include "ControlledMotorDriver.h"
#include <Arduino.h>

void ControlledMotorDriver::update(){
  unsigned long current_time = micros();
  if ((current_time - this->last_calculation) > this-> update_time){
    tachometer.calculate_rpm();
    this->rpm = tachometer.get_rpm();
  
    *this->error_signal = this->set_point - this->rpm;

    pid.calculate_output();

    physical_driver.set_throttle(*this->output_signal);
    this->last_calculation = current_time;
  }
}

void ControlledMotorDriver::enable(){
}
