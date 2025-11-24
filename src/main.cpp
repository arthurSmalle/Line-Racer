#include <Arduino.h>

#include "state machine/FSM.h"
//#include "robot states/RSInit.h"
#include "state machine/StatesEnum.h"
// states that will be used
#include "robot states/RSAdjustOnStraight.h"

#include "robot states/TSSpeakers.h"
#include "robot states/TSAngleController.h"

  
  // global objects
  // RSInit * rsinit = new RSInit(StatesEnum::AdjustOnStraight);
  // TSSpeakers * speaker = new TSSpeakers();
  TSAngleController * anglecontroller = new TSAngleController();
//  RSAdjustOnStraight * straigt = new RSAdjustOnStraight();
  FSM fsm = FSM(anglecontroller);
  
  void setup(){
    Serial.begin(115200);
#ifdef IMU
    IMU.begin();
#endif
  }

void loop(){
  fsm.update();
}
