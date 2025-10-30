#ifndef RS_CURVE_H
#define RS_CURVE_H
#include "state machine/RobotState.h"
#include <Arduino.h>

class RSCurve : public RobotState{
  public:
    RSCurve(){}
 
  private:
    // put code between {} to implement features
    void enter() override{}
    void update() override{}
    // add logic for going to next state here
    State * go_next_state() override{}
};

#endif
