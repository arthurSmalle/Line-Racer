#ifndef RS_CURVE_H 
#define RS_CURVE_H
#include "state machine/RobotState.h"
#include <Arduino.h>

class RSCurve : public RobotState{
  public:
    RSCurve(){}
  private:
    //===========//
    // variables //
    //===========//
    float base_speed = 40;
    float turn_factor = 30; 
    bool straigth_detected = false; // for state transision to curve logic
    //===========//
    // functions //
    //===========//


    //====================//
    // override functions //
    //====================//
    void enter() override{
      motor_cl_l.enable();
      motor_cl_r.enable();
      motor_cl_l.set_set_point(base_speed);
      motor_cl_r.set_set_point(base_speed);
    }

    void update() override{
      RobotState::update();
      Serial.println("CURVE STATE");

      unsigned long current_time = millis();

      Serial.println();

      motor_cl_l.set_set_point(base_speed + (get_angle_pid_output() * turn_factor));
      motor_cl_r.set_set_point(base_speed - (get_angle_pid_output() * turn_factor));

      // detect if needed adjustment
      if (angle_controller.get_ir_triggered()){
	if ((current_time - time_since_last_adjustment) >= curve_treshold){
	  straigth_detected = true;
	  this->next_ready = true;
	} else {
	  time_since_last_adjustment = current_time;
	}
      }

    }

    // add logic for going to next state here
    State * go_next_state() override;

    static unsigned long time_since_last_adjustment; // detect if still in a curve, otherwise adjust to straight line logic
    const static unsigned long curve_treshold; // treshold for determining if the robot is in a curve or not
};

unsigned long RSCurve::time_since_last_adjustment = 0;
const unsigned long RSCurve::curve_treshold = 400;

// this needs to be defined after the class is delacered (otherwise refrence to RSAdjustOnStraight not found)
State * RSCurve::go_next_state(){
  if (straigth_detected){
  }
}

#endif
