#include <Arduino.h>
#include "Monitor.h"

void SpeedMonitor::refresh_data(){
  // implement reading speed monitor 
  //this->monitored_data;
}

void AngleMonitor::refresh_data(){
  // implement reading speed monitor 
  //this->monitored_data;
  float angle_estimate = 0;
  #if IR_AMOUNT == 3
  // calculate estimate angle based on IR reading
    bool ir_pin0 = digitalRead(IR_PIN0);
    bool ir_pin1 = digitalRead(IR_PIN1);
//    bool ir_pin2 = digitalRead(IR_PIN2);
    float max_angle = tan(SYMM_TO_IR / WHEELS_TO_IR);
  #endif
};
