#include <Arduino.h>
#include "PID/PIDController.h"
#include "motor control/L298NController.h"
#include "angle control/IRsensorPrediction.h"

float error_signal = 10;
float output_signal;
PIDController pid = PIDController(0.7, 0.3, 0.1, error_signal);
IRSensorPrediction ir_sens = IRSensorPrediction();
L298NController motor_l = L298NController(MOTOR_L1, MOTOR_L2, 50);
L298NController motor_r = L298NController(MOTOR_R1,MOTOR_R2, 50);

void setup(){
  Serial.begin(115200);
}

void loop(){
  error_signal = ir_sens.predict_angle();
  pid.set_error_signal(error_signal);
  pid.calculate_output();
  output_signal = pid.get_output_signal();
  // drive the motors with the new output signal
  motor_l.set_throttle(50 - error_signal);
  motor_r.set_throttle(50 + error_signal);
 
  // for testing purposses (no irl usecase BUT AFFECTS THE PERFORMANCE OF HW)
  error_signal = error_signal - output_signal * 0.1;
  Serial.println("pid value" + String(output_signal));
  Serial.println("Error: " + String(error_signal));
  delay(250);
}
