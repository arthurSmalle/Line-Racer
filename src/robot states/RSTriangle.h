#ifndef RS_TRIANGLE_H
#define RS_TRIANGLE_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>


class RSTriangle : public RobotState{
  public:
    RSTriangle(){};
  protected:
    float set_point = 20;
    float turn_gain = 1.2;
    unsigned long start_time;
    const unsigned long max_duration = 2000;

    void enter() override{
      start_time = millis();
      motor_cl_l.set_set_point(set_point);
      motor_cl_r.set_set_point(set_point);
    }

    void update() override{
      RobotState::update();

      float left_speed = set_point - turn_gain * get_angle_pid_output();
      float right_speed = set_point + turn_gain * get_angle_pid_output();
      left_speed = constrain(left_speed, -set_point, set_point);
      right_speed = constrain(right_speed, -set_point, set_point);
      motor_cl_l.set_set_point(left_speed);
      motor_cl_r.set_set_point(right_speed);

      if (abs(get_angle()) > 10) {
        start_time = millis();
      }

      if (millis() - start_time > max_duration){
        this->next_ready = true;
      }
    }

    StatesEnum go_next_state() override{
    }    
};

#endif
