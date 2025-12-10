#include "RSCurve.h"
#include "state machine/RobotState.h"
unsigned long RSCurve::time_since_last_adjustment = 0;
const unsigned long RSCurve::curve_treshold = 400;

void RSCurve::update(){
      RobotState::update();
      Serial.println("CURVE STATE");

      unsigned long current_time = millis();

      Serial.println();

      motor_cl_l.set_set_point(base_speed + (get_angle_pid_output() * turn_factor));
      motor_cl_r.set_set_point(base_speed - (get_angle_pid_output() * turn_factor));

      // detect if needed adjustment
      if (angle_controller.get_ir_triggered()){
	if ((current_time - time_since_last_adjustment) >= curve_treshold){
	  straigth_detected = true;
	  this->next_ready = true;
	} else {
	  time_since_last_adjustment = current_time;
	}
      }

    }
