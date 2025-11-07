#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H
#include "State.h"
#include "../motor control/ControlledMotorDriver.h"
#include "../angle control/IRSensorPrediction.h"
#include "../PID/PIDController.h"

class RobotState: public State{
  public:
    RobotState():State(){};
  protected:
    // get and set functions
    float get_angle(){return angle;};
    float get_angle_pid_output(){return angle_output_signal;}
    float get_angle_pid_set_point(){return angle_pid.get_set_point();}

    float set_angle_error(const float error){angle_error_signal = error;}
    float set_angle_pid_set_point(const float set_point){angle_pid.set_set_point(set_point);}


    // override functions
    void virtual update() override{
      // make reading for the angle
      ir_sens.update_ir_readings();
      angle = ir_sens.predict_angle();

      // calculate output with the pid
      angle_error_signal = angle;
      angle_pid.update();
    }

    // static objects
    static IRSensorPrediction ir_sens;
    static PIDController angle_pid;
    static ControlledMotorDriver motor_cl_l;
    static ControlledMotorDriver motor_cl_r;

  private:
    // static variables
    static float angle; // keep track of the angle deviation of the robot
    static float angle_error_signal; // error signal (input for pid) (only angle estimate needed for input, set point will be subtracted automatically)
    static float angle_output_signal; // output of the angle pid
};

// initialize the static fields of this class
IRSensorPrediction RobotState::ir_sens = IRSensorPrediction();
ControlledMotorDriver RobotState::motor_cl_l = ControlledMotorDriver(10, 2400, MOTOR_L1, MOTOR_L2, TACHO_PIN0A, 0);
ControlledMotorDriver RobotState::motor_cl_r = ControlledMotorDriver(0, 2400, MOTOR_R1, MOTOR_R2, TACHO_PIN1A, 1);
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
float RobotState::angle_error_signal = 0;
float RobotState::angle_output_signal = 0;
#endif
