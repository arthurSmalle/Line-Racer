#ifndef RS_TEMPLATE_H
#define RS_TEMPLATE_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>

// WHEN ADDING A NEW STATE, ADD IT TO THE STATESENUM AND ADD IT TO FSM 

class RSTemplate : public RobotState{
  public:
    // constructor (leave empty)
    // change name to name of class
    RSTemplate(){}

  protected:
    // Add variables here

    // Add functions here
    // functions can only be called from enter, update and go_next_state
    void example_func(){}

    // put code between {} to implement features

    // do something on start of the state (only does this once)
    void enter() override{
      // do check on angle and set rpm for motor
      if (get_angle() < 0){
      motor_cl_r.set_set_point(30);
      motor_cl_l.set_set_point(30);
      } else {
      motor_cl_r.set_set_point(20);
      motor_cl_l.set_set_point(20);
      }
    }

    // keep looping
    void update() override{
      RobotState::update(); // roep dit aan (enkel in update) om de angle telkens up te daten
      motor_cl_l.update();
      motor_cl_r.update();
    }
    // add logic for going to next state here
    // this is called when in in main you do:
    // ready_go_next = true;
    // this ends the update loop!
    StatesEnum go_next_state() override{}
};

#endif
