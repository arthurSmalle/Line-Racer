#ifndef RS_ADJUST_ON_STRAIGHT_H
#define RS_ADJUST_ON_STRAIGHT_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>

class RSAdjustOnStraight : public RobotState{
  public:
    RSAdjustOnStraight(){}
  private:
    //===========//
    // variables //
    //===========//
    float base_speed = 300;
    float turn_modifier = 180;
    bool curve_detected = false; // for state transision to curve logic
    unsigned long start_time = 0; // time stamp for when state was initialzed
    
    //===========//
    // functions //
    //===========//


    //====================//
    // override functions //
    //====================//
    void enter() override;
    void update() override;
     StatesEnum go_next_state() override;

    const static unsigned long curve_treshold; // treshold for determining if the robot is in a curve or not
};
#endif
