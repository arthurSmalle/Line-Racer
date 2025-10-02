#include <Arduino.h>

#include "PID/PIDController.h"

float error_signal;
float output_signal;

void setup(){
  Serial.begin(115200);
  PIDController pid = PIDController(0.5, 0.5, 0.5, error_signal);
  
}

void loop(){
  Serial.println("wheel to ir " + String(WHEELS_TO_IR));
}
