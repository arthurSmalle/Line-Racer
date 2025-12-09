//#include "../music player/music.h"
#include "RSAdjustOnStraight.h"
unsigned long RSAdjustOnStraight::time_since_last_adjustment = 0;
const unsigned long RSAdjustOnStraight::curve_treshold = 1000;
unsigned long start_time;

void RSAdjustOnStraight::enter(){
  start_time = millis();
  Serial.println("ENTERED STRAINGADJUST");
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
    RobotState::update();

      unsigned long current_time = millis();
      float throttled_speed = time_throttle(base_speed, base_speed -100, start_time, start_time + 4000);

      // DEBUG PRINT
      float p, i, d;
      p = angle_pid.get_P_out();
      i = angle_pid.get_I_out();
      i = angle_pid.get_D_out();
      motor_cl_l.set_set_point(throttled_speed + (get_angle_pid_output() * turn_modifier ));
      motor_cl_r.set_set_point(throttled_speed - (get_angle_pid_output() *turn_modifier));
      Serial.println("$$P-auto," + String(get_angle()) + ","+ String(get_angle_pid_output()) + "," + String(p) + ","+ String(d)+ "," + String(this->time_since_last_adjustment));
      
      // detect adjustments
      if (detect_rising_edge(angle_controller.get_ir_triggered())){
	digitalWrite(13, LOW);
//	if (!just_started){
	  time_since_last_adjustment = current_time;
	// } else {
	//   just_started = false;
	// }
      }
      // detect if takes to long to adjust
      if ((current_time - time_since_last_adjustment) >= 100){
	  // if (!just_started){
	    curve_detected = true;
	    next_ready = true;
	  // } else {
	  // }
      }
}

StatesEnum RSAdjustOnStraight::go_next_state(){
      digitalWrite(13, HIGH);
      if (curve_detected){
	return StatesEnum::Curve;
      }
    }
