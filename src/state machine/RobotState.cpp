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

      // calculate output with the pid (use only with 2 sensors)
      if (this->pid_mode){
	angle_error_signal -= angle_output_signal * .1;
	if (detect_rising_edge(angle_controller.get_ir_triggered())){
	  if (angle > 0){
	    angle_error_signal += 100;
	  } else {
	    angle_error_signal -= 100;
	  }
	}
      } else { // if not in pid mode take the raw angle output
	angle_error_signal = angle;
      }
      angle_pid.update();

      // update the moters
      motor_cl_l.update();
      motor_cl_r.update();
    }

// gives back the speed to throttle the max speed with over time
// speed - time throttle
float RobotState::time_throttle(float s_max, float s_min, unsigned long start_time, unsigned long end_time){
  if (millis() > end_time){
    float s_diff = s_max - s_min;
    unsigned long time_diff = end_time - millis();
    unsigned long total_time = end_time - start_time;
    float time_mod = float(time_diff)/ float(total_time);
    return s_diff * (1 - time_mod);
  } else{
    return s_min;
  }
}

bool RobotState::detect_rising_edge(const bool new_edge){
  if ((this->last_edge == false) and (new_edge == true)){
    return  true;
    this->last_edge = new_edge;
  }
  else{
    return false;
    this->last_edge = new_edge;
  }
}
