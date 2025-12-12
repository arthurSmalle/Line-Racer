#include "RSCurve.h"
#include "state machine/RobotState.h"
const unsigned long RSCurve::super_curve_treshold = 850;
const unsigned long RSCurve::straigth_treshold = 250;

void RSCurve::enter(){
  digitalWrite(13, LOW);
  motor_cl_l.set_clock_wise(false);
  motor_cl_l.enable();
  motor_cl_r.enable();
  motor_cl_l.set_set_point(base_speed);
  motor_cl_r.set_set_point(base_speed);
  angle_pid.set_Kp(12);
  angle_pid.set_Ki(0); // default
  angle_pid.set_Kd(0); // default
  }

void RSCurve::update(){
  // UPDATE MOTORS AND CONTROL
  RobotState::update();
  motor_cl_l.set_set_point(base_speed + (get_angle_pid_output() * turn_modifier ));
  motor_cl_r.set_set_point(base_speed - (get_angle_pid_output() *turn_modifier));
  // // STATE TRANSISION DETECTION
  if (get_average_adjustment_time() < straigth_treshold){
    this->next_ready = true;
    this->straigth_detected = true;
  }
  // if (get_time_since_last_adjustment() > super_curve_treshold){
  //   this->next_ready = true;
  //   this->super_curve_detected = true;
  // }
  // DEBUG PRINT
#ifdef DEBUG
  float p;
  p = angle_pid.get_P_out();
  Serial.println("$$P-auto," + String(get_angle()) + ","+ String(get_angle_pid_output()) + "," + String(p) + "," + String(get_time_since_last_adjustment())+"," + String(get_average_adjustment_time()) + ",00,"+ String(get_last_peak()) + ",10" );
  // note: 10 is code for this state (usefull to see in plotting software)
#endif
}

StatesEnum RSCurve::go_next_state(){
      if (super_curve_detected){
	return StatesEnum::SuperCurve;
      } else if (straigth_detected){
	return StatesEnum::AdjustOnStraight;
      }
    }
