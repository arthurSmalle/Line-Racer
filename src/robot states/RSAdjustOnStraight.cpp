//#include "../music player/music.h"
#include "RSAdjustOnStraight.h"
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
const unsigned long RSAdjustOnStraight::curve_treshold = 300;

void RSAdjustOnStraight::enter(){
  this->start_time = millis();
  digitalWrite(13, HIGH);
  motor_cl_l.set_clock_wise(false);
  motor_cl_l.enable();
  motor_cl_r.enable();
  motor_cl_l.set_set_point(base_speed);
  motor_cl_r.set_set_point(base_speed);
  angle_pid.set_Kp(9);
  angle_pid.set_Ki(0); // default
  angle_pid.set_Kd(0); // default
  }

void RSAdjustOnStraight::update(){
  // UPDATE MOTORS AND CONTROL
  RobotState::update();
  music_player.update();
  motor_cl_l.set_set_point(base_speed + (get_angle_pid_output() * turn_modifier ));
  motor_cl_r.set_set_point(base_speed - (get_angle_pid_output() *turn_modifier));
  // STATE TRANSISION DETECTION
  if (get_time_since_last_adjustment() > curve_treshold){
    this->next_ready = true;
    this->curve_detected = true;
  }
  // DEBUG PRINT
#ifdef DEBUG
  float p;
  p = angle_pid.get_P_out();
  // Serial.println("$$P-auto," + String(get_angle()) + ","+ String(get_angle_pid_output()) + "," + String(p) + "," + String(get_time_since_last_adjustment())+"," + String(get_average_adjustment_time()) + ",30" );
  // note: 30 is code for this state (usefull to see in plotting software)
#endif
}

StatesEnum RSAdjustOnStraight::go_next_state(){
      if (curve_detected){
	return StatesEnum::Curve;
      }
    }
