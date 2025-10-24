#include <Arduino.h>
#include "PID/PIDController.h"
#include "motor control/ControlledMotorDriver.h"
#include "angle control/IRSensorPrediction.h"

  // constants
  const float BASE_RPM = 30;
  const float TURNING_RPM = 15;
  const float ANGLE_AMP = 10;
  const float TURN_RATE = 20; // if > 1 makes turnrate faster
  
 
  // global vars
  float error_signal = 0;
  float angle = 0;
  float estimated_angle = 0;
  float output_signal = 0;
  // test turning speed vars
  const uint8_t MEASURE_SCOPE = 10;
  unsigned long measured_vals[MEASURE_SCOPE] = {0};
  
  // global objects
  IRSensorPrediction ir_sens = IRSensorPrediction();
  ControlledMotorDriver motor_cl_l = ControlledMotorDriver(30,MOTOR_L1, MOTOR_L2, TACHO_PIN0A, 0);
  ControlledMotorDriver motor_cl_r = ControlledMotorDriver(30,MOTOR_R1, MOTOR_R2, TACHO_PIN1A, 1);

  PIDController angle_pid = PIDController(0.8, 0.0, 0.5, error_signal);

  void setup(){
    Serial.begin(115200);
    motor_cl_l.set_clock_wise(false);
  }

void drive_sensor_feedback_cl(){
  // update motor values
   motor_cl_l.update();
   motor_cl_r.update();
 
   // get the angle
   ir_sens.update_ir_readings();
   float angle_reading = ir_sens.predict_angle() * ANGLE_AMP; // TIMES 10 TO AMP SIGNAL TODO: MAKE PRECISES LATER
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

  output_signal = angle_pid.update(estimated_angle);

  estimated_angle -= output_signal / ANGLE_AMP;
   if (angle != 0){
     motor_cl_l.set_set_point(TURNING_RPM - output_signal * TURN_RATE);
     motor_cl_r.set_set_point(TURNING_RPM + output_signal * TURN_RATE);
     Serial.println("SPL: " + String(TURNING_RPM + output_signal * TURN_RATE));
     Serial.println("SPR: " + String(TURNING_RPM - output_signal * TURN_RATE));
   } else {
     motor_cl_l.set_set_point(BASE_RPM - output_signal);
     motor_cl_r.set_set_point(BASE_RPM + output_signal);
     Serial.println("SPL: " + String(BASE_RPM + output_signal));
     Serial.println("SPR: " + String(BASE_RPM - output_signal));
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

void test_turn_speed(const float start_rpm, const float interval_rpm, bool dual_drive, const float test_interval = 1500){
  if (dual_drive){
    motor_cl_l.set_clock_wise(true);
  }
  // iterate over the tests
  for (uint8_t i = 0; i < MEASURE_SCOPE; i++){
    Serial.println("Setting rpm: " + String(start_rpm + i*interval_rpm));
    motor_cl_l.set_set_point(start_rpm + i*interval_rpm);
    motor_cl_r.set_set_point(start_rpm + i*interval_rpm);

    unsigned long start_time = millis();
    digitalWrite(13, LOW);

    while(digitalRead(IR_PIN0) == LOW){
      Serial.println("TURING");
      motor_cl_l.update();
      if (dual_drive){
	motor_cl_r.update();
      }
      delay(100);
    }
    measured_vals[i] = millis() - start_time;
    Serial.println("done turining: " + String(measured_vals[i]));
    digitalWrite(13, HIGH);
    delay(test_interval);
  }
  digitalWrite(13, HIGH);
  while(1){
    Serial.println("====================");
    for (uint8_t i = 0; i < MEASURE_SCOPE; i++){
      Serial.println("Meting " + String(i) + " = " + String(measured_vals[i]));
    }
    delay(500);
  }
}

void loop(){
  motor_cl_l.update();
//  Serial.println("RPM: " + String(motor_cl_l.get_rpm()));
//  drive_sensor_feedback_cl();
//  test_turn_speed(10,10,false);
}
