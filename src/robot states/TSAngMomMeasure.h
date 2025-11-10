#ifndef TS_ANG_MOM_MEASURE_H
#define TS_ANG_MOM_MEASURE_H

#include "../state machine/RobotState.h"

#define AMOUNT_OF_MEASUREMENTS 10

class TSAngMomMeasure : public RobotState{
  public:
    TSAngMomMeasure(){}

  protected:
    // Add variables here
    unsigned long measurement_list[AMOUNT_OF_MEASUREMENTS] = {};

    void enter() override{
      motor_cl_l.set_set_point(0);
      motor_cl_r.set_set_point(0);
      motor_cl_l.enable();
      motor_cl_r.enable();
    }

    // keep looping
    void update() override{
      float last_angle = this->get_angle();
      RobotState::update(); // roep dit aan (enkel in update) om de angle telkens up te daten
      // detect if ir sens is triggered
      if (angle_controller.get_ir_triggered()){
	motor_cl_l.stop();
	motor_cl_r.stop();
      } else {
	// detect overshooting
	if (last_angle != this->get_angle()){
	  // TODO IMPLEMENT CORRECTION FOR OVERSHOOTING
	}
      }

    }

    State * go_next_state() override{}
};

#endif
