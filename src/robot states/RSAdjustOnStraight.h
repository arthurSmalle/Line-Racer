#ifndef RS_ADJUST_ON_STRAIGHT_H
#define RS_ADJUST_ON_STRAIGHT_H
#include "state machine/RobotState.h"
#include <Arduino.h>

// include states to transision to
#include "RSCurve.h"

class RSAdjustOnStraight : public RobotState{
  public:
    RSAdjustOnStraight(){}
  private:
    //===========//
    // variables //
    //===========//
    float base_speed = 30;
    bool curve_detected = false; // for state transision to curve logic
    
    //===========//
    // functions //
    //===========//


    //====================//
    // override functions //
    //====================//
    void enter() override{
      unsigned long current_time = millis();
      
      // check if time since last adjustment is small enough to trigger curve logic
      if ((current_time - time_since_last_adjustment) <= curve_treshold){
	curve_detected = true;
	this->next_ready = true;
      }
      time_since_last_adjustment = current_time;
    }

    void update() override{}

    // add logic for going to next state here
    State * go_next_state() override{
      if (curve_detected){
	return new RSCurve();
      }
    }

    static unsigned long time_since_last_adjustment; // keep track of when last adjusted to predict if the robot is in a curve
    const static unsigned long curve_treshold; // treshold for determining if the robot is in a curve or not
};

unsigned long RSAdjustOnStraight::time_since_last_adjustment = 0;
const unsigned long RSAdjustOnStraight::curve_treshold = 200;
#endif
