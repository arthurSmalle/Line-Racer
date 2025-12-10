#include "RSSuperCurve.h"
#include "state machine/StatesEnum.h"
const unsigned long RSSuperCurve::curve_treshold = 1000;
void RSSuperCurve::enter(){
#ifdef DEBUG
  Serial.println("ENTERED SUPERCURVE");
#endif
  motor_cl_l.set_clock_wise(false);
  motor_cl_l.enable();
  motor_cl_r.enable();
  motor_cl_l.set_set_point(base_speed);
  motor_cl_r.set_set_point(base_speed);
  angle_pid.set_Kp(15);
  angle_pid.set_Ki(0); // default
  angle_pid.set_Kd(0); // default
  }

void RSSuperCurve::update(){
  // UPDATE MOTORS AND CONTROL
  RobotState::update();
  motor_cl_l.set_set_point(base_speed + (get_angle_pid_output() * turn_modifier ));
  motor_cl_r.set_set_point(base_speed - (get_angle_pid_output() *turn_modifier));
  // STATE TRANSISION DETECTION
  if (get_average_adjustment_time() < curve_treshold){
    this->next_ready = true;
    this->curve_detected = true;
  }
  // DEBUG PRINT
#ifdef DEBUG
  float p;
  p = angle_pid.get_P_out();
  Serial.println("$$P-auto," + String(get_angle()) + ","+ String(get_angle_pid_output()) + "," + String(p) + "," + String(get_time_since_last_adjustment())+ "," + "20");
  // note: 20 is code for this state (usefull to see in plotting software)
#endif
}

StatesEnum RSSuperCurve::go_next_state(){
      if (curve_detected){
	return StatesEnum::Curve;
      }
}
