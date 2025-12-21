#ifndef RS_EMERGENCY_H
#define RS_EMERGENCY_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>


class RSEmergency : public RobotState{
  public:
    unsigned long emergency_start_time;
    RSEmergency(){
    }

  protected:
    // do something on start of the state (only does this once)
    void enter() override{
      emergency_start_time = millis();
       motor_cl_l.set_set_point(250);
       motor_cl_r.set_set_point(250);
    }

    // keep looping
    void update() override{
      // init flipper
      float flipper = 10;
      // set motorspeed
       motor_cl_l.set_set_point(250 + flipper);
       motor_cl_r.set_set_point(250 - flipper);
      RobotState::update(); // roep dit aan (enkel in update) om de angle telkens up te daten
      // make sure robot drives forward
      if (millis() - emergency_start_time > 100){
	flipper *= -1;
      }
      // exit emergency_state
      if (millis() - emergency_start_time > 2000){
	next_ready = true;
      }
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
