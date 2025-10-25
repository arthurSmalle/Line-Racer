#ifndef RS_ADJUST_ON_STRAIGHT_H
#define RS_ADJUST_ON_STRAIGHT_H
#include "state machine/RobotState.h"
#include <Arduino.h>

class RSAdjustOnStraight : public RobotState{
  public:
    RSAdjustOnStraight(){}
  private:
    float base_speed = 30;


    void enter() override{}
    void update() override{}
    // add logic for going to next state here
    State * go_next_state() override{}
   
    // constructor (leave empty)
};

#endif
