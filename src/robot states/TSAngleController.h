#ifndef TS_ANGLECONTROLLER_H
#define TS_ANGLECONTROLLER_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>

class TSAngleController : public RobotState{
  public:
    // constructor (leave empty)
    // change name to name of class
    TSAngleController(){}

  protected:

#ifdef IMU
    int calibration_measurse = 30;
    void calibrate_angle(){
      delay(3000);
      Serial.println("ENTERED THE ANGLE CONTROLLER STATE");
      motor_cl_l.stop();
      motor_cl_r.stop();
      Serial.println("CALIBRATION FOR ZP");
      angle_controller.set_mag_zp(calibration_measurse);
      motor_cl_l.enable();
      motor_cl_r.enable();
      motor_cl_l.set_set_point(0);
      motor_cl_r.set_set_point(0);
      motor_cl_l.set_clock_wise(false);
      motor_cl_r.set_clock_wise(true);
      
      while (!angle_controller.get_ir_triggered()){
	Serial.println("looping to get to the line");
	RobotState::update(); // roep dit aan (enkel in update) om de angle telkens up te daten
	motor_cl_l.set_set_point(30);
      }
      motor_cl_l.set_set_point(0);
      angle_controller.set_mag_angle_ref(calibration_measurse);
    }
#endif

    void enter() override{
#ifdef IMU
      calibrate_angle();
#endif
    }

    // keep looping
    void update() override{
      RobotState::update(); // roep dit aan (enkel in update) om de angle telkens up te daten
    

#ifdef IMU
      float mag_angle = angle_controller.get_predicted_angle();
      float angle_in_degree = mag_angle * 180/PI;
      float x,y,z;
      float x_zp, y_zp, z_zp;
      angle_controller.get_IMU_DATA(x, y, z);
      // angle_controller.get_zp_data(x_zp, y_zp, z_zp);
      // Serial.println("$$P-auto,"+ String(mag_angle)+","+String(angle_in_degree)+","+ String(x_zp-x)+","+String(y_zp-y)+","+String(z_zp - z));
      Serial.println("$$P-auto,"+ String(x)+","+String(y)+","+String(z));
#endif
    }

    StatesEnum go_next_state() override{}
};

#endif
