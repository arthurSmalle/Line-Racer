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
      motor_cl_l.set_set_point(0);
      motor_cl_r.set_set_point(0);
      music_player.stop();
    }

    // keep looping
    void update() override{
      RobotState::update(); // roep dit aan (enkel in update) om de angle telkens up te daten
#ifdef DEBUG
  // Serial.println("$$P-auto,00,00,00,00,00");
  // note: 00 is code for this state (usefull to see in plotting software)
#endif
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
