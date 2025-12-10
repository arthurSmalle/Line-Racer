#include "RSSuperCurve.h"
#include "state machine/StatesEnum.h"

void RSSuperCurve::enter(){
      Serial.println("ENTERED SuperCurve");
      motor_cl_l.set_clock_wise(false);
      motor_cl_l.enable();
      motor_cl_r.enable();
      motor_cl_l.set_set_point(base_speed);
      motor_cl_r.set_set_point(base_speed);
      angle_pid.set_Kp(9);
      angle_pid.set_Ki(0); // default
      angle_pid.set_Kd(0); // default
    }

void RSSuperCurve::update(){
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
      Serial.println("$$P-auto," + String(get_angle()) + ","+ String(get_angle_pid_output()) + "," + String(p) + ","+ String(d));

}
