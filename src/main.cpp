#include <Arduino.h>

#include "state machine/FSM.h"
#include "robot states/RSInit.h"
#include "state machine/StatesEnum.h"
// states that will be used

  // constants
  const float BASE_RPM = 30;
  const float TURNING_RPM = 15;
  const float ANGLE_AMP = 10;
  const float TURN_RATE = 20; // if > 1 makes turnrate faster
  
  // global objects
  RSInit * rsinit = new RSInit(StatesEnum::AdjustOnStraight);

  FSM fsm = FSM(rsinit);
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
