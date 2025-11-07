#ifndef RSTRIANGLE
#define RSTRIANGLE
#include "state machine/RobotState.h"
#include <Arduino.h>

class RSTriangle : protected RobotState{
  private:
    // Add variables here
    float side_length = 30;
    float turn_angle = 120;

    // Add functions here
    void example_func(){
      side_length++;
    }

    // put code between {} to implement features
    void enter() override{}
    void update() override{}
    void exit() override{}
    // add logic for going to next state here
    State * go_next_state() override{}
   
    // constructor (leave empty)
    RSTriangle(){}
};

#endif