#include <Arduino.h>
#include "PID/PIDController.h"
#include "motor control/L298NController.h"
#include "motor control/ControlledMotorDriver.h"
#include "angle control/IRSensorPrediction.h"

#include "state machine/FSM.h"
// states that will be used
#include "robot states/RSDriveForward.h"
#include "robot states/TSTachometer.h"

  // constants
  const float BASE_RPM = 30;
  const float TURNING_RPM = 15;
  const float ANGLE_AMP = 10;
  const float TURN_RATE = 20; // if > 1 makes turnrate faster
  
  // global objects
  RSDriveForward * forward = new RSDriveForward();
  TSTachometer * tacho_test = new TSTachometer(40);
  FSM fsm = FSM(tacho_test);
  // global vars
  float error_signal = 0;
  float angle = 0;
  float estimated_angle = 0;
  float output_signal = 0;
  // test turning speed vars
  const uint8_t MEASURE_SCOPE = 10;
  unsigned long measured_vals[MEASURE_SCOPE] = {0};
  
  void setup(){
    Serial.begin(115200);
  }

void loop(){
  fsm.update();
}
