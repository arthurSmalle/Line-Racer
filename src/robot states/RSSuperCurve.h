#ifndef RS_SUPER_CURVE_H 
#define RS_SUPER_CURVE_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>

class RSSuperCurve : public RobotState{
  public:
    RSSuperCurve(){}
  private:
    //===========//
    // variables //
    //===========//
    float base_speed = 40;
    float turn_modifier = 30; 
    bool curve_detected = false; // for state transision to curve logic
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
