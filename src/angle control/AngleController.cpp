#include "AngleController.h"
#include "angle control/IRSensorPrediction.h"

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

  // update the magdata
  this->IntegratedMag->update();
// #ifdef DEBUG
//   float x,y,z;
//   this->IntegratedMag->get_mag_data(x, y, z);
//   Serial.println("$$P-auto,"+String(x)+","+String(y)+","+String(y));
// #endif
  this->predicted_angle =  this->IntegratedMag->get_angle_to_zero();
}
// ---------------- //
// MAGMETER PROGRAM //
// ---------------- //

// STALS PROGRAM
void AngleController::get_average_mag_data(float &x,float &y,float &z, int measurments){
  float x_measure, y_measure, z_measure = 0;
  Serial.println("entering average data func");
  int measure_count = 0;
#ifdef DEBUG 
  Serial.println("looping..."); 
#endif
  while (measure_count < measurments){
    if (this->IntegratedMag->is_mag_ready()){
#ifdef DEBUG
      Serial.println("MAG AVERAGE MEASURE: " + String(measure_count));
#endif
      this->IntegratedMag->get_mag_data(x_measure, y_measure, z_measure);
      x += x_measure;
      y += y_measure;
      z += z_measure;
      measure_count++;
    } else {
#ifdef DEBUG
      Serial.println("MAG NOT READY");
#endif
    }
  }
#ifdef DEBUG
  Serial.println("Passed the measurments loop");
#endif
  x_measure /= measurments;
  y_measure /= measurments;
  z_measure /= measurments;
}

// STALS PROGRAM
void AngleController::set_mag_zp(const int measurments){
#ifdef DEBUG
  Serial.println("entering set zp func");
#endif
  float x_measure, y_measure, z_measure = 0;
  this->get_average_mag_data(x_measure, y_measure, z_measure, measurments);
  this->IntegratedMag->set_zero_point(x_measure, y_measure, z_measure);
}

// STALS PROGRAM
void AngleController::set_mag_angle_ref(const int measurments,float rad){
  // get the angle from the ir
  if (rad == 0){
    rad = this->ir_sens.get_max_angle();
  }
  float x_measure, y_measure, z_measure = 0;
  get_average_mag_data(x_measure, y_measure, z_measure, measurments);
  this->IntegratedMag->set_angle_to_magdata_ref(rad, x_measure, y_measure, z_measure);
}
