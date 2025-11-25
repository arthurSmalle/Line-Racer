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

    void set_angle_error(const float error){angle_error_signal = error;}
    void set_angle_pid_set_point(const float set_point){angle_pid.set_set_point(set_point);}


    // override functions
    void virtual update() override{
      // make reading for the angle
      angle_controller.update();
      angle = angle_controller.get_real_angle(); // TODO: implement the predicted angle

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
#endif
