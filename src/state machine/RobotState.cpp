#include "RobotState.h"
// initialize the static fields of this class
ControlledMotorDriver RobotState::motor_cl_l = ControlledMotorDriver(0, 1, MOTOR_L1, MOTOR_L2, TACHO_PIN0A, 0);
ControlledMotorDriver RobotState::motor_cl_r = ControlledMotorDriver(0, 1, MOTOR_R1, MOTOR_R2, TACHO_PIN1A, 1);
AngleController RobotState::angle_controller = AngleController(&motor_cl_l, &motor_cl_r);
MusicPlayer RobotState::music_player = MusicPlayer(MUSIC_PIN);

// variables for angle pid
float Kp = 0.7;
float Ki = 0;
float Kd = 0;
float resolution = 0.01;
float time_component = 10;
float set_point = 0;

PIDController RobotState::angle_pid =  PIDController(Kp, Ki, Kd, resolution, time_component, set_point, &RobotState::angle_error_signal, &RobotState::angle_output_signal);

// static variables
float RobotState::angle = 0;
float RobotState::angle_error_signal = 0;
float RobotState::angle_output_signal = 0;

void RobotState::update(){
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
