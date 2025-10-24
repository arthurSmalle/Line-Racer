#ifndef RS_DRIVE_FORWARD_H
#define RS_DRIVE_FORWARD_H
#include "state machine/RobotState.h"

class RSDriveForward : public RobotState{
  public:
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

    void exit() override{}
    State go_next_state() override{}
};

#endif
