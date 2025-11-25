//#include "../music player/music.h"
#include "RSAdjustOnStraight.h"
unsigned long RSAdjustOnStraight::time_since_last_adjustment = 0;
const unsigned long RSAdjustOnStraight::curve_treshold = 1000;


void RSAdjustOnStraight::enter(){
      Serial.println("ENTERED STRAINGADJUST");
      motor_cl_l.set_clock_wise(false);
      motor_cl_l.enable();
      motor_cl_r.enable();
      motor_cl_l.set_set_point(base_speed);
      motor_cl_r.set_set_point(base_speed);
      angle_pid.set_Kp(2); // default
      angle_pid.set_Ki(0); // default
      angle_pid.set_Kd(0); // default
    }

void RSAdjustOnStraight::update(){
      RobotState::update();

      unsigned long current_time = millis();

      // DEBUG PRINT
      float p, i, d;
      p = angle_pid.get_P_out();
      i = angle_pid.get_I_out();
      i = angle_pid.get_D_out();
      motor_cl_l.set_set_point(base_speed );
      motor_cl_r.set_set_point(base_speed );
      motor_cl_l.set_set_point(base_speed + (get_angle_pid_output() * turn_modifier ));
      motor_cl_r.set_set_point(base_speed - (get_angle_pid_output() *turn_modifier));
      Serial.println("$$P-auto," + String(get_angle()) + ","+ String(get_angle_pid_output()) + "," + String(p) + ","+ String(i) + ","+ String(d) );

      // mumziek saus //
      // music_player.set_loop(true);
      // music_player.set_song(tokyo_melody, tokyo_durations, tokyo_size, .75);
      // music_player.play();
      // einde muziek saus //

      // detect if needed adjustment
	//      if (angle_controller.get_ir_triggered()){
	// if ((current_time - time_since_last_adjustment) <= curve_treshold){
	//   curve_detected = true;
	//   this->next_ready = true;
	// } else {
	//   time_since_last_adjustment = current_time;
	// }
	//      }

}
