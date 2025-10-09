#include "Tachometer.h"
#include <Arduino.h>
#define MILLIS_IN_MINUTE 3600

void Tachometer::enable(){
  this->is_enabled = true;
  just_enabled = true;
  if (id == 0){
    attachInterrupt(digitalPinToInterrupt(pin), set_new_prev_time0, RISING);
  } else {
    attachInterrupt(digitalPinToInterrupt(pin), set_new_prev_time1, RISING);
  }
}

void Tachometer::disable(){
  this->is_enabled = false;
  just_enabled = false;
}

tacho_err_t Tachometer::calculate_rpm(){
  // check if there is a problem
  if (is_enabled != false){
    return tacho_err_not_en;
  }
  if (just_enabled == true){
    return tacho_err_no_prev;
  }
  // continue if there is no problem
  this->rpm = float(MILLIS_IN_MINUTE) / (millis() - this->prev_time[id]);
}

