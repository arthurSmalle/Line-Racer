#ifndef TS_MOTORCL_H 
#define TS_MOTORCL_H
#include "state machine/RobotState.h"
#include <Arduino.h>

class TSMOTORCTL : public RobotState{
  public:
    // constructor (leave empty)
    // change name to name of class
    TSMOTORCTL(){}
    float speed = 0;
    unsigned long last_adjust = 0;

  protected:
    // do something on start of the state (only does this once)
    void enter() override{
      motor_cl_l.set_clock_wise(false);
    }

    // keep looping
    void update() override{
      unsigned long current_time = millis();
      RobotState::update(); // roep dit aan (enkel in update) om de angle telkens up te daten
      if ( (current_time - last_adjust) > 4000){
	last_adjust = current_time;
	speed += 10;
      }
      if (speed >= 200){
	digitalWrite(13, HIGH);
	speed = 0;
      }
      motor_cl_l.set_set_point(speed);
//      motor_cl_r.set_set_point(speed);
      //output
      float rpm = motor_cl_l.get_rpm();
      float p = motor_cl_l.get_P_value();
      float i = motor_cl_l.get_I_value();
      float d = motor_cl_l.get_D_value();
      Serial.println("$$P-auto,"+String(speed)+","+String(rpm)+","+String(p)+","+String(i)+","+String(d));
    }
    // add logic for going to next state here
    // this is called when in in main you do:
    // ready_go_next = true;
    // this ends the update loop!
    State * go_next_state() override{}
};

#endif
