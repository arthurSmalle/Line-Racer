#include "AngleController.h"

void AngleController::update(){
  // reset the const flags
  this->ir_triggered = false; 
  this->outside_ir_range = false;

  // check if the ir is triggering
  this->ir_sens.update_ir_readings();
  float ir_last_data = this->ir_sens.get_last_perdiciont();
  float ir_data = this->ir_sens.predict_angle();
  
  // reset the angle to fixed angle dictated by the ir sensors
  if (ir_data != 0){
    ir_triggered = true;
    this->real_angle = ir_last_data;
  }

  // check if left ir sens range (based on potential gyro measurment)
  if (abs(this->predicted_angle) > ir_sens.get_max_angle()){
    this->outside_ir_range = true;
  }
}

void AngleController::set_mag_zp(const int measurments){
  float x_measure, y_measure = 0;
}
