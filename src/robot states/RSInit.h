#ifndef RS_INIT_H
#define RS_INIT_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>

class RSInit : public RobotState{
  public:
    RSInit(StatesEnum next){
      this->next_state = next;
    }

  protected:
    StatesEnum next_state;

    // do something on start of the state (only does this once)
    void enter() override{
      RobotState::motor_cl_l.set_clock_wise(false);
      RobotState::motor_cl_l.enable();
      RobotState::motor_cl_r.enable();
    }

    // keep looping
    void update() override{
      RobotState::update(); // roep dit aan (enkel in update) om de angle telkens up te daten
      this->next_ready = true;
    }
    // add logic for going to next state here
    // this is called when in in main you do:
    // ready_go_next = true;
    // this ends the update loop!
    StatesEnum go_next_state() override{
      return this->next_state;
    }
};

#endif
