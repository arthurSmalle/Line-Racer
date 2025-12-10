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
    float base_speed = 40;
    float turn_factor = 30; 
    bool straigth_detected = false; // for state transision to curve logic
    //===========//
    // functions //
    //===========//


    //====================//
    // override functions //
    //====================//
    void enter() override{
      motor_cl_l.enable();
      motor_cl_r.enable();
      motor_cl_l.set_set_point(base_speed);
      motor_cl_r.set_set_point(base_speed);
    }

    void update() override;

    // add logic for going to next state here
    StatesEnum go_next_state() override{
      if (straigth_detected){
	return StatesEnum::AdjustOnStraight;
      }
    }

    static unsigned long time_since_last_adjustment; // detect if still in a curve, otherwise adjust to straight line logic
    const static unsigned long curve_treshold; // treshold for determining if the robot is in a curve or not
};
#endif
