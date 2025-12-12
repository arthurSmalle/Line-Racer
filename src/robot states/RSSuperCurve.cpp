#include "RSSuperCurve.h"
#include "state machine/State.h"
#include "state machine/StatesEnum.h"
#include <cstdio>
bool current_angle_edge = false;
const int RSSuperCurve::curve_big_peak_treshold = 4;
void RSSuperCurve::enter(){
  motor_cl_l.set_clock_wise(false);
  motor_cl_l.enable();
  motor_cl_r.enable();
  motor_cl_l.set_set_point(0);
  motor_cl_r.set_set_point(0);
  angle_pid.set_Kp(20);
  angle_pid.set_Ki(0); // default
  angle_pid.set_Kd(0); // default
  }

void RSSuperCurve::update(){
  // UPDATE MOTORS AND CONTROL
  RobotState::update();
  music_player.update();
  motor_cl_l.set_set_point(base_speed + (get_angle_pid_output() * turn_modifier ));
  motor_cl_r.set_set_point(base_speed - (get_angle_pid_output() *turn_modifier));
  // if (get_angle_pid_output() > 0){
  //  motor_cl_l.set_set_point(250);
  //  motor_cl_r.set_set_point(30);
  // } else {
  //  motor_cl_l.set_set_point(30);
  //  motor_cl_r.set_set_point(250);
  // }
  // STATE TRANSISION DETECTION
  if (get_peak_detected()){
    update_amount_of_big_peaks();
  }
  if (get_amount_of_big_peaks() < curve_big_peak_treshold){
    this->next_ready = true;
    this->curve_detected = true;
  }
  // DEBUG PRINT
#ifdef DEBUG
  float p;
  p = angle_pid.get_P_out();
  // Serial.println("$$P-auto," + String(get_angle()) + ","+ String(get_angle_pid_output()) + "," + String(p) + "," + String(get_time_since_last_adjustment())+"," + String(get_average_adjustment_time())+ "," + String(get_amount_of_big_peaks())+ "," + String(get_last_peak()) + ",20" );
  // note: 20 is code for this state (usefull to see in plotting software)
#endif
}

StatesEnum RSSuperCurve::go_next_state(){
      if (curve_detected){
	return StatesEnum::Curve;
      }
}

void RSSuperCurve::update_amount_of_big_peaks(){
  unsigned long peak = get_last_peak();
  if (peak > 200){
    this->peak_list[this->peak_index] = peak;
  } else {
    this->peak_list[this->peak_index] = 700;
  }
  Serial.println("=====");
  Serial.println("peak: " +String(peak));
  Serial.println("peak index: " +String(peak_index));
  Serial.println("=====");
  this->peak_index++;
  if (this->peak_index >= PEAK_MEMORY){
    this->peak_index = 0;
    this->full_peak_cycle_done = true;
  }
}

int RSSuperCurve::get_amount_of_big_peaks(){
  unsigned long peak_treshhold = 600;
  if (full_peak_cycle_done){
    int big_peak_count = 0;
    for (int i =0; i < PEAK_MEMORY; i++){
      Serial.println(String(this->peak_list[i]));
      if (this->peak_list[i] >= peak_treshhold){
	big_peak_count++;
      }
    }
    Serial.println("Big peaks: " + String(big_peak_count));
    Serial.println("====================");
    return big_peak_count;
  } else {
    return PEAK_MEMORY;
  }
}
