#ifndef RS_EMERGENCY_H
#define RS_EMERGENCY_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>

class RSEmergency : public RobotState{
  public:
    RSEmergency(){
    }

  protected:
    // do something on start of the state (only does this once)
    void enter() override{
      angle_controller.emergency_flip();
    }

    // keep looping
    void update() override{
      this->next_ready = true;
      RobotState::update(); // roep dit aan (enkel in update) om de angle telkens up te daten
#ifdef DEBUG
  Serial.println("$$P-auto,00,00,00,00,50");
  // note: 50 is code for this state (usefull to see in plotting software)
#endif
    }
    // add logic for going to next state here
    // this is called when in in main you do:
    // ready_go_next = true;
    // this ends the update loop!
    StatesEnum go_next_state() override{
      return StatesEnum::Curve;
    }
};

#endif
