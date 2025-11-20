#include <Arduino.h>

#include "state machine/FSM.h"
//#include "robot states/RSInit.h"
#include "state machine/StatesEnum.h"
// states that will be used
#include "robot states/RSAdjustOnStraight.h"

#include "robot states/TSSpeakers.h"
#include "robot states/TSMagnetometer.h"

  // constants
  const float BASE_RPM = 30;
  const float TURNING_RPM = 15;
  const float ANGLE_AMP = 10;
  const float TURN_RATE = 20; // if > 1 makes turnrate faster
  
  // global objects
  RSInit * rsinit = new RSInit(StatesEnum::AdjustOnStraight);
  TSSpeakers * speaker = new TSSpeakers();
  TSMagnetometer * magmeter = new TSMagnetometer();
//  RSAdjustOnStraight * straigt = new RSAdjustOnStraight();
  FSM fsm = FSM(rsinit);
  
  void setup(){
    Serial.begin(115200);
  }

void loop(){
  fsm.update();
}
