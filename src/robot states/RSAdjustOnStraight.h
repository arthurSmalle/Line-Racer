#ifndef RS_ADJUST_ON_STRAIGHT_H
#define RS_ADJUST_ON_STRAIGHT_H
#include "api/Compat.h"
#include "state machine/RobotState.h"
#include <Arduino.h>

#include "RSCurve.h"

class RSAdjustOnStraight : public RobotState{
  public:
    RSAdjustOnStraight(){}
  private:
    //===========//
    // variables //
    //===========//
    float base_speed = 40;
    bool curve_detected = false; // for state transision to curve logic
    
    //===========//
    // functions //
    //===========//


    //====================//
    // override functions //
    //====================//
    void enter() override{
      motor_cl_l.set_clock_wise(false);
      motor_cl_l.enable();
      motor_cl_r.enable();
      motor_cl_l.set_set_point(base_speed);
      motor_cl_r.set_set_point(base_speed);
    }

    void update() override{
      RobotState::update();
      Serial.println("STRAIGHT STATE");

      unsigned long current_time = millis();

      // DEBUG PRINT

      // motor_cl_l.set_set_point(base_speed );
      // motor_cl_r.set_set_point(base_speed );
      Serial.println("Angle: " + String(get_angle()));
      Serial.println("PID output: " + String(get_angle_pid_output()));
      motor_cl_l.set_set_point(base_speed + get_angle_pid_output());
      motor_cl_r.set_set_point(base_speed - get_angle_pid_output());
      // detect if needed adjustment
	//      if (angle_controller.get_ir_triggered()){
	// if ((current_time - time_since_last_adjustment) <= curve_treshold){
	//   curve_detected = true;
	//   this->next_ready = true;
	// } else {
	//   time_since_last_adjustment = current_time;
	// }
	//      }

    }

    // add logic for going to next state here
    State * go_next_state() override;

    static unsigned long time_since_last_adjustment; // keep track of when last adjusted to predict if the robot is in a curve
    const static unsigned long curve_treshold; // treshold for determining if the robot is in a curve or not
};

unsigned long RSAdjustOnStraight::time_since_last_adjustment = 0;
const unsigned long RSAdjustOnStraight::curve_treshold = 1000;

// this needs to be defined after the class is delacered (otherwise refrence to RSCurve not found)
State * RSAdjustOnStraight::go_next_state(){
  digitalWrite(13, HIGH);
  if (curve_detected){
    return new RSCurve();
  }
}

#endif
