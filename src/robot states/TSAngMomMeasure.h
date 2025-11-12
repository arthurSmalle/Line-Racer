#ifndef TS_ANG_MOM_MEASURE_H
#define TS_ANG_MOM_MEASURE_H

#include "../state machine/RobotState.h"

#define AMOUNT_OF_MEASUREMENTS 10

class TSAngMomMeasure : public RobotState{
  public:
    TSAngMomMeasure(){}

  protected:
    // Add variables here
    unsigned long set_point_list[AMOUNT_OF_MEASUREMENTS];
    unsigned long measurement_list[AMOUNT_OF_MEASUREMENTS] = {};

    void single_motor_test(unsigned long measurement_list[], const int measurement_list_size){
      motor_cl_l.stop();
      motor_cl_r.stop();
      // update while not triggering the ir sensor
      for ( int i = 0; i < measurement_list_size; i++){
	// reset to take new measurement
	motor_cl_r.set_set_point(20);
	motor_cl_r.enable();
	motor_cl_r.set_clock_wise(false);
	while(!angle_controller.get_ir_triggered()){
      	  RobotState::update();
	}
	motor_cl_r.set_clock_wise(true);
        
	// take measurements
	unsigned long start_time = micros();
      	motor_cl_r.enable();
	motor_cl_r.set_set_point(set_point_list[i]);

	while(!angle_controller.get_ir_triggered()){
      	  RobotState::update();
      	}
	measurement_list[i] = start_time - micros();
      	motor_cl_r.stop();
      }
    }

    void enter() override{
      motor_cl_l.set_set_point(0);
      motor_cl_r.set_set_point(0);
      motor_cl_l.enable();
      motor_cl_r.enable();
    }

    // keep looping
    void update() override{
      // generate setpoint list
      for (int i = 0; i < AMOUNT_OF_MEASUREMENTS; i++){
	set_point_list[i] = i + 20;
      }
      single_motor_test(this->measurement_list, AMOUNT_OF_MEASUREMENTS);
      digitalWrite(13, HIGH);
      for (int i = 0; i < AMOUNT_OF_MEASUREMENTS; i++){
	Serial.println("set point: " + String(set_point_list[i]));
	Serial.println("measurement: " + String(measurement_list[i]));
      }
    }

    State * go_next_state() override{}
};

#endif
