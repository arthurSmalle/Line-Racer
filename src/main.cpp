#include <Arduino.h>

#include "state machine/FSM.h"
//#include "robot states/RSInit.h"
#include "state machine/StatesEnum.h"
// states that will be used
#include "robot states/RSAdjustOnStraight.h"

#include "robot states/TSSpeakers.h"
#include "robot states/TSAngleController.h"
#ifdef USE_IMU
#include "robot states/TSMagnetometer.h"
#endif

  // global objects
  // RSInit * rsinit = new RSInit(StatesEnum::AdjustOnStraight);
  // TSSpeakers * speaker = new TSSpeakers();
  // TSAngleController * anglecontroller = new TSAngleController();
 RSAdjustOnStraight * straight = new RSAdjustOnStraight();
  FSM fsm = FSM(straight);
  
  void setup(){
    Serial.begin(115200);
#ifdef USE_IMU
    IMU.begin();
#endif
  }

void loop(){
  fsm.update();
}
