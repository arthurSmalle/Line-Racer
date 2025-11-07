#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H
#include "State.h"
#include "../motor control/ControlledMotorDriver.h"
#include "../angle control/IRSensorPrediction.h"
#include "../PID/PIDController.h"
#include <set>

class RobotState: public State{
  public:
    RobotState():State(){};
  protected:
    // override functions
    void virtual update() override{
      ir_sens.update_ir_readings();
      angle = ir_sens.predict_angle();
    }
    // static variables
    static float angle; // keep track of the angle deviation of the robot
    static float angle_set_point;
    static float angle_error_signal;
    static float angle_output_signal;


    // static objects
    static IRSensorPrediction ir_sens;
    static PIDController angle_pid;
    static ControlledMotorDriver motor_cl_l;
    static ControlledMotorDriver motor_cl_r;
};

// initialize the static fields of this class
IRSensorPrediction RobotState::ir_sens = IRSensorPrediction();
ControlledMotorDriver RobotState::motor_cl_l = ControlledMotorDriver(10, 50, MOTOR_L1, MOTOR_L2, TACHO_PIN0A, 0);
ControlledMotorDriver RobotState::motor_cl_r = ControlledMotorDriver(0, 50, MOTOR_R1, MOTOR_R2, TACHO_PIN1A, 1);
// variables for angle pid
float Kp = 0.8;
float Ki = 0.4;
float Kd = 0.1;
float resolution = 0.01;
float time_component = 100;
float set_point = 0;

PIDController RobotState::angle_pid =  PIDController(Kp, Ki, Kd, resolution, time_component, set_point, &RobotState::angle_error_signal, &RobotState::angle_output_signal);

// static variables
float RobotState::angle = 0;
float RobotState::angle_set_point = 0;
float RobotState::angle_error_signal = 0;
float RobotState::angle_output_signal = 0;
#endif
