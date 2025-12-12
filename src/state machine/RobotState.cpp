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
unsigned long RobotState::adjust_intervals[ADJUST_INTERVAL_SAMPLES] = {}; // store x amount of adjust intervals
unsigned long RobotState::time_since_last_adjustment = 0;
int RobotState::adjust_intervals_index = 0;
unsigned long RobotState::last_adjustment_time = 0;
unsigned long RobotState::last_peak_time = 0;
bool RobotState::peak_detected = false;

// overide functions
void RobotState::update(){
      // make reading for the angle
      angle_controller.update();
      angle = angle_controller.get_real_angle(); // TODO: implement the predicted angle
      peak_detected = detect_rising_edge(angle_controller.get_ir_triggered());
      update_adjust_time_info(peak_detected);

      // calculate output with the pid
      angle_error_signal = angle;
      angle_pid.update();

      // update the moters
      motor_cl_l.update();
      motor_cl_r.update();
    }

// getters

unsigned long RobotState::get_time_since_last_adjustment(){return time_since_last_adjustment;}
unsigned long RobotState::get_average_adjustment_time(){
      unsigned long total_time = 0;
      for (int i = 0; i < ADJUST_INTERVAL_SAMPLES; i++){
	total_time += adjust_intervals[i];
      }
      return (total_time / ADJUST_INTERVAL_SAMPLES);
    }

// extra functions
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
    this->last_edge = new_edge;
    return  true;
  }
  else{
    this->last_edge = new_edge;
    return false;
  }
}

void RobotState::update_adjust_time_info(bool rising_edge){
  unsigned long new_time_since_last_adjustment = millis() - last_adjustment_time;
  // detect if the robot makes a new adjustment
  if (rising_edge){
    last_peak_time = new_time_since_last_adjustment;
    Serial.println("Last peak robot: " + String(last_peak_time));
    last_adjustment_time = millis();
  }
  // check if time since last adjustment smaller then new time
  if (last_peak_time <= new_time_since_last_adjustment){
    // only add if bigger to only capture the values above the peaks
    adjust_intervals[adjust_intervals_index] = time_since_last_adjustment;
  }
  // set new time for time since last adjustment
  time_since_last_adjustment = new_time_since_last_adjustment;
  // keep track of position in the list for calculating averages
  adjust_intervals_index++;
  if (adjust_intervals_index >= ADJUST_INTERVAL_SAMPLES){
    adjust_intervals_index = 0;
  }
}
