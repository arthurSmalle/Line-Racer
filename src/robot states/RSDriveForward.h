#ifndef RS_DRIVE_FORWARD_H
#define RS_DRIVE_FORWARD_H
#include "state machine/RobotState.h"
#include <Arduino.h>

class RSDriveForward : protected RobotState{
  protected:
    float set_point = 30;

    RSDriveForward(){}
    void enter() override{
      motor_cl_l.set_set_point(set_point);
      motor_cl_r.set_set_point(set_point);
    }

    void update() override{
      motor_cl_l.update();
      motor_cl_r.update();
    }
};

#endif
