#include "MagMeterController.h"

float MagMeterController::get_angle_to_zero(){
  if (!angle_ref_set || !zp_set){
#ifdef DEBUG
    Serial.println("angle ref or zp not set!");
#endif
    return 0;
  } else {
    if (!angle_to_tan_scale_set){
#ifdef DEBUG
      Serial.println("calculating tan scale");
#endif
      calculate_angle_to_tan_scale();
    }
// #ifdef DEBUG
//     Serial.println("x_zp: " + String(this->x_zp));
//     Serial.println("x_zp: " + String(this->y_zp));
//     Serial.println("x: " + String(this->x));
//     Serial.println("y: " + String(this->y));
//     Serial.println("angle scale:" + String(this->angle_to_tan_scale));
// #endif
    return tan((this->x_zp - this->x)/(this->y_zp - this->y)) * this->angle_to_tan_scale;
  }
}

void MagMeterController::calculate_angle_to_tan_scale(){
    if (!angle_ref_set || !zp_set){
      angle_to_tan_scale = 0;
    } else {
      float angle = tan ((this->x_zp - this->x_angle_ref) / (this->y_zp - this->y_angle_ref));
      angle_to_tan_scale = angle_ref / angle;
      angle_to_tan_scale_set = true;
    }
   }

void MagMeterController::update(){
  get_mag_data(this->x, this->y, this->z);
}
