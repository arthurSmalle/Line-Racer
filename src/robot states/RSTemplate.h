#ifndef RS_TEMPLATE_H
#define RS_TEMPLATE_H
#include "state machine/RobotState.h"
#include <Arduino.h>

class RSDriveForward : protected RobotState{
  private:
    // Add variables here
    float example_var = 30;

    // Add functions here
    void example_func(){
      example_var++;
    }

    // put code between {} to implement features
    void enter() override{}
    void update() override{}
    void exit() override{}
    // add logic for going to next state here
    State * go_next_state() override{}
   
    // constructor (leave empty)
    RSDriveForward(){}
};

#endif
