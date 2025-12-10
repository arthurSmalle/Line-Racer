
#ifndef RS_TOKYO
#define RS_TOKYO
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>

class RSTokyo : public RobotState{
  public:
    RSTokyo(){}
  private:
    //===========//
    // variables //
    //===========//
    float base_speed = 140;
    int drift_time = 3000; // time the robot drifts in ms

    //====================//
    // override functions //
    //====================//
    void enter() override;
    void update() override;
     StatesEnum go_next_state() override;
};
#endif
