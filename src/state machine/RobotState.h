#ifndef ROBOT_STATE_H
#define ROBOT_STATE_H
#include "State.h"
#include "../motor control/ControlledMotorDriver.h"
#include "../angle control/AngleController.h"
#include "../music player/MusicPlayer.h"
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
      angle_controller.update();
      angle = angle_controller.get_predicted_angle();

      // calculate output with the pid
      angle_error_signal = angle;
      angle_pid.update();

      // update the moters
      motor_cl_l.update();
      motor_cl_r.update();
    }

    // static objects
    static PIDController angle_pid;
    static ControlledMotorDriver motor_cl_l;
    static ControlledMotorDriver motor_cl_r;
    static AngleController angle_controller;
    static MusicPlayer music_player;

  private:
    // static variables
    static float angle; // keep track of the angle deviation of the robot
    static float angle_error_signal; // error signal (input for pid) (only angle estimate needed for input, set point will be subtracted automatically)
    static float angle_output_signal; // output of the angle pid
};

// initialize the static fields of this class
ControlledMotorDriver RobotState::motor_cl_l = ControlledMotorDriver(0, 1, MOTOR_L1, MOTOR_L2, TACHO_PIN0A, 0);
ControlledMotorDriver RobotState::motor_cl_r = ControlledMotorDriver(0, 1, MOTOR_R1, MOTOR_R2, TACHO_PIN1A, 1);
AngleController RobotState::angle_controller = AngleController(&motor_cl_l, &motor_cl_r);
MusicPlayer RobotState::music_player = MusicPlayer(MUSIC_PIN);

// variables for angle pid
float Kp = 0.5;
float Ki = 0;
float Kd = 10;
float resolution = 0.01;
float time_component = 10;
float set_point = 0;

PIDController RobotState::angle_pid =  PIDController(Kp, Ki, Kd, resolution, time_component, set_point, &RobotState::angle_error_signal, &RobotState::angle_output_signal);

// static variables
float RobotState::angle = 0;
float RobotState::angle_error_signal = 0;
float RobotState::angle_output_signal = 0;
#endif
