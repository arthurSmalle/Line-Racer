#ifndef RS_DRIVE_FORWARD_H
#define RS_DRIVE_FORWARD_H
#include "state machine/RobotState.h"
#include <Arduino.h>

// import states to transision to
#include "RSAdjustOnStraight.h"

class RSDriveForward : public RobotState{
  public:
    RSDriveForward(){}
  protected:
    float set_point = 30;

    void enter() override{
      motor_cl_l.set_set_point(set_point);
      motor_cl_r.set_set_point(set_point);
    }

    void update() override{
      // update the motors
      motor_cl_l.update();
      motor_cl_r.update();

      // check if there is a deviation in the angle
      ir_sens.update_ir_readings();
      angle = ir_sens.predict_angle();
      
      if (angle != 0){
	this->next_ready = true;
      }
    }

    State * go_next_state() override{
      return new RSAdjustOnStraight();
    }
};

#endif