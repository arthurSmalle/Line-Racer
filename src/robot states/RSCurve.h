#ifndef RS_CURVE_H 
#define RS_CURVE_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>

class RSCurve : public RobotState{
  public:
    RSCurve(){}
  private:
    //===========//
    // variables //
    //===========//
    float base_speed = 240;
    float turn_modifier = 180; 
    bool straigth_detected = false; // for state transision to curve logic
    bool super_curve_detected = false; // for state transision to curve logic
    //===========//
    // functions //
    //===========//


    //====================//
    // override functions //
    //====================//
    void enter() override;
    void update() override;
    StatesEnum go_next_state() override;

    const static unsigned long super_curve_treshold; // treshold for determining if the robot is in a sharp curve or not
    const static unsigned long straigth_treshold; // treshold for determining if the robot is on a relative straight line
};
#endif
