#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H
#include "State.h"
#include "../motor control/ControlledMotorDriver.h"
#include "../angle control/IRSensorPrediction.h"

class RobotState: public State{
  public:
    RobotState():State(){};
  protected:

    static IRSensorPrediction ir_sens;
    static ControlledMotorDriver motor_cl_l;
    static ControlledMotorDriver motor_cl_r;
};

// initialize the static fields of this class
IRSensorPrediction RobotState::ir_sens = IRSensorPrediction();
ControlledMotorDriver RobotState::motor_cl_l = ControlledMotorDriver(10, 50, MOTOR_L1, MOTOR_L2, TACHO_PIN0A, 0);
ControlledMotorDriver RobotState::motor_cl_r = ControlledMotorDriver(0, 50, MOTOR_R1, MOTOR_R2, TACHO_PIN1A, 1);
#endif
