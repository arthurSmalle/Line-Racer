#include <Arduino.h>
#include "PID/PIDController.h"
#include "motor control/L298NController.h"

float error_signal = 10;
float output_signal;
PIDController pid = PIDController(0.7, 0.3, 0.1, error_signal);

void setup(){
  Serial.begin(115200);
}

void loop(){
  pid.calculate_output();
  output_signal = pid.get_output_signal();
  error_signal = error_signal - output_signal * 0.1;
  pid.set_error_signal(error_signal);
  Serial.println("pid value" + String(output_signal));
  Serial.println("Error: " + String(error_signal));
  delay(250);
}
