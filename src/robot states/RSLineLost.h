#ifndef RS_LINE_LOST_H
#define RS_LINE_LOST_H
#include "state machine/RobotState.h"
#include <Arduino.h>

class RSLineLost : public RobotState{
  public:
    RSLineLost(RobotState* previous) : previous_state(previous){}
  protected:
    RobotState* previous_state;
    float set_point = 20;
    unsigned long lost_start_time = 0;
    unsigned long reverse_start_time = 0;
    const unsigned long time_before_reverse = 1000;
    const unsigned long max_reverse_time = 2000;
    bool line_found = false;

    void enter() override{
        lost_start_time = 0;
        reverse_start_time = 0;
        line_found = false;
      motor_cl_l.set_set_point(0);
      motor_cl_r.set_set_point(0);
    }

    void update() override{
        ir_sens.update_ir_readings();
        angle = ir_sens.predict_angle();
    
        if (angle != 0){
          line_found = true;
          this->next_ready = true;
        }

        else {
            if (lost_start_time == 0){
                lost_start_time = millis();
            }
            else if ((millis() - lost_start_time) >= time_before_reverse){
                if (reverse_start_time == 0){
                    reverse_start_time = millis();
                motor_cl_l.set_set_point(-set_point);
                motor_cl_r.set_set_point(-set_point);
                }

                if ((millis() - reverse_start_time) >= max_reverse_time){
                    this->next_ready = true;
                }
            }
        }

        motor_cl_l.update();
        motor_cl_r.update();
    }

    State * go_next_state() override{
      return previous_state;
    }   
};

#endif