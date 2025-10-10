#include <Arduino.h>
#include "PID/PIDController.h"
#include "motor control/L298NController.h"
#include "motor control/Tachometer.h"
#include "angle control/IRsensorPrediction.h"

float error_signal = 10;
float output_signal;

float rpm_l = 0;
float rpm_r = 0;
float base_rpm = 30;
float error_rpm_l = 0;
float error_rpm_r = 0;

IRSensorPrediction ir_sens = IRSensorPrediction();
L298NController motor_l = L298NController(MOTOR_L1, MOTOR_L2, 50);
L298NController motor_r = L298NController(MOTOR_R1,MOTOR_R2, 50);
Tachometer tacho_l = Tachometer(TACHO_PIN0, 0);
Tachometer tacho_r = Tachometer(TACHO_PIN1, 1);

PIDController angle_pid = PIDController(0.7, 0.3, 0.1, error_signal);
PIDController motor_l_pid = PIDController(0.7, 0.3, 0.1, error_signal);
PIDController motor_r_pid = PIDController(0.7, 0.3, 0.1, error_signal);


void setup(){
  Serial.begin(115200);
  tacho_l.enable();
  tacho_r.enable();
}


// try to follow the line with the rpm of the motors also controlled in closed lope configuration
void drive_motor_cl(){
  // drive the motors using rpm instead of %
  if (tacho_l.calculate_rpm() == tacho_ok){
    rpm_l = tacho_l.get_rpm();
  }
  
  if (tacho_r.calculate_rpm() == tacho_ok){
    rpm_r = tacho_r.get_rpm();
  }
  
  // calculate error on the rpm 
  error_rpm_l = base_rpm - rpm_l;
  error_rpm_r = base_rpm - rpm_r;
  
  // drive the motor with the error signal
  motor_l.set_throttle(error_rpm_l);
  motor_r.set_throttle(error_rpm_r);
#ifdef DEBUG
  Serial.println("rpm: "+ String(rpm_l));
#endif
}

// try to follow the line with the motors in open loop configuration
void drive_motor_ol(){
  error_signal = ir_sens.predict_angle();
  angle_pid.set_error_signal(error_signal);
  angle_pid.calculate_output();
  output_signal = angle_pid.get_output_signal();
  // drive the motors with the new output signal (simple methode)
  motor_l.set_throttle(50 - error_signal);
  motor_r.set_throttle(50 + error_signal);
}

void loop(){
  drive_motor_cl();

  // for testing purposses (no irl usecase BUT AFFECTS THE PERFORMANCE OF HW)
  error_signal = error_signal - output_signal * 0.1;
  Serial.println("pid value" + String(output_signal));
  Serial.println("Error: " + String(error_signal));
  delay(250);
}
