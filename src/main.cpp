#include <Arduino.h>
#include "PID/PIDController.h"
#include "motor control/L298NController.h"
#include "motor control/Tachometer.h"
#include "motor control/ControlledMotorDriver.h"
#include "angle control/IRSensorPrediction.h"

  float error_signal = 0;
  float output_signal;
  float base_rpm = 30;
  float turning_rpm = 15;
  float angle = 0;
  float estimated_angle = 0;

  float rpm_l = 0;
  float rpm_r = 0;
  float error_rpm_l = 0;
  float error_rpm_r = 0;

  IRSensorPrediction ir_sens = IRSensorPrediction();
  L298NController motor_l = L298NController(MOTOR_L1, MOTOR_L2, 100);
  L298NController motor_r = L298NController(MOTOR_R1,MOTOR_R2, 50);
//  Tachometer tacho_l = Tachometer(TACHO_PIN0A, TACHO_PIN0B, 0);
//  Tachometer tacho_r = Tachometer(TACHO_PIN1A, TACHO_PIN1B, 1);
  ControlledMotorDriver motor_cl_l = ControlledMotorDriver(30,MOTOR_L1, MOTOR_L2, TACHO_PIN0A, 0);
  ControlledMotorDriver motor_cl_r = ControlledMotorDriver(30,MOTOR_R1, MOTOR_R2, TACHO_PIN1A, 1);

  PIDController angle_pid = PIDController(0.8, 0.0, 0.5, error_signal);
  PIDController motor_l_pid = PIDController(0.7, 0.3, 0.1, error_signal);
  PIDController motor_r_pid = PIDController(0.7, 0.3, 0.1, error_signal);


  void setup(){
    Serial.begin(115200);
    motor_cl_l.set_clock_wise(false);
    // tacho_l.enable();
   // tacho_r.enable();
  }


  // try to follow the line with the rpm of the motors also controlled in closed lope configuration
  void drive_motor_cl(const float set_point){
    // tacho_l.calculate_rpm();
    // rpm_l = tacho_l.get_rpm();
    // calculate error on the rpm
    error_rpm_l = set_point - rpm_l;

    motor_l_pid.set_error_signal(error_rpm_l);
    
    // drive the motor with the error signal
    motor_l_pid.calculate_output();
    motor_l.set_throttle(motor_l_pid.get_output_signal());
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

void test_tachometer(){
  float set_point = 1;
  motor_l.set_throttle(20);
  // tacho_l.calculate_rpm();
  // rpm_l = tacho_l.get_rpm();
  // Serial.println("RPM main loop:" + String(rpm_l));
}

void drive_sensor_feedback_cl(){
  // update motor values
   motor_cl_l.update();
   motor_cl_r.update();
 
   // get the angle
   ir_sens.update_ir_readings();
   float angle_reading = ir_sens.predict_angle() * 10; // TIMES 10 TO AMP SIGNAL TODO: MAKE PRECISES LATER
   if (angle_reading != angle){
    angle = angle_reading;
    estimated_angle = angle_reading;
   }
   // PID controlled estimation for the actual angle
   // set the built in led high if there is a angle != 0
   if (angle != 0){
     digitalWrite(13, HIGH);
   }
   else {
     digitalWrite(13, LOW);
   }

  angle_pid.set_error_signal(estimated_angle);
  angle_pid.calculate_output();
  output_signal = angle_pid.get_output_signal();

  estimated_angle -= output_signal / 10;
  output_signal *= 10; // AMP the output signal
   if (angle != 0){
     motor_cl_l.set_set_point(turning_rpm - output_signal);
     motor_cl_r.set_set_point(turning_rpm + output_signal);
     Serial.println("SPL: " + String(turning_rpm + output_signal));
     Serial.println("SPR: " + String(turning_rpm - output_signal));
   } else {
     motor_cl_l.set_set_point(base_rpm - output_signal);
     motor_cl_r.set_set_point(base_rpm + output_signal);
     Serial.println("SPL: " + String(base_rpm + output_signal));
     Serial.println("SPR: " + String(base_rpm - output_signal));
   }
 
   Serial.println("Angle: " + String(angle));
   Serial.println("E Angle: " + String(estimated_angle));
   Serial.println("output_signal: " + String(output_signal));
   delay(100);
}

void test_ir(){
  if (digitalRead(IR_PIN0)){
    Serial.println("IR 0 high");
  } else {
    Serial.println("IR 0 low");
  }
  if (digitalRead(IR_PIN1)){
    Serial.println("IR 1 high");
  } else {
    Serial.println("IR 1 low");
  }

}

void loop(){
  drive_sensor_feedback_cl();
}
