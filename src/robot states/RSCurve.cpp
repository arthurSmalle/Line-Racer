#include "RSCurve.h"
unsigned long RSCurve::time_since_last_adjustment = 0;
const unsigned long RSCurve::curve_treshold = 400;

// gives back the speed to throttle the max speed with over time
// speed - time throttle
unsigned long curve_start_time;
float curve_time_throttle(float s_max, float s_min, float time_max){
  float s_diff = s_max - s_min;
  float time_diff = float(10^6 *(micros() - curve_start_time));
  float time_mod = (time_max - time_diff) / time_max;
  return s_diff * (1 - time_mod);
}

bool curve_last_edge = false;
bool curve_detect_rising_edge(const bool new_edge){
  if ((curve_last_edge == false) and (new_edge == true)){
    return  true;
    curve_last_edge = new_edge;
  }
  else{
    return false;
    curve_last_edge = new_edge;
  }
}

void RSCurve::enter(){
      motor_cl_l.enable();
      motor_cl_r.enable();
      motor_cl_l.set_set_point(base_speed);
      motor_cl_r.set_set_point(base_speed);
      angle_pid.set_Kp(10);
      angle_pid.set_Ki(0); // default
      angle_pid.set_Kd(0); // default
    }
void RSCurve::update(){
      RobotState::update();
      Serial.println("CURVE STATE");

      unsigned long current_time = millis();

      Serial.println();

      motor_cl_l.set_set_point(base_speed + (get_angle_pid_output() * turn_factor));
      motor_cl_r.set_set_point(base_speed - (get_angle_pid_output() * turn_factor));

      // detect adjustments
      if (curve_detect_rising_edge(angle_controller.get_ir_triggered())){
	  time_since_last_adjustment = current_time;
      }
      // detect if takes to long to adjust
      if ((current_time - time_since_last_adjustment) <= 2000){
	    straigth_detected = true;
	    next_ready = true;
	    motor_cl_r.stop();
	    motor_cl_l.stop();
      }
    }
