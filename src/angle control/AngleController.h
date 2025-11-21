#ifndef ANGLE_CONTROLLER_H
#define ANGLE_CONTROLLER_H
#include "IRSensorPrediction.h"
#include "../motor control/ControlledMotorDriver.h"
#include "angle control/MagMeterController.h"
#ifdef ARDUINO_NANO_BLE
#include "LSM9DS1Controller.h"
#endif ARDUINO_NANO_BLE

class AngleController{
  public:
    void update(); // update all the measurements and calculations
    float get_real_angle(){return this->real_angle;} // get the "real angle" determined by one of the sensors on runtime
    // TODO implement automatic balancing of real and predicted_angle (based on time since laste measurement)
    float get_predicted_angle(){return this->predicted_angle;} // get a estimate of the angle determined by calculations and tests before runtime
    unsigned long get_time_since_real_measured(); // get time since the real angle was measured (to avoid using "old" data)
    bool get_is_outside_ir_range(); // get if the real angle is outside the infrared sensor range (meaning the robot goes off track!)
    bool get_ir_triggered(){return this->ir_triggered;}

    // WARNING THIS WILL STALL THE PROGRAM
    void set_mag_zp(const int measurements);

    AngleController(const ControlledMotorDriver * motor_cl_l, const ControlledMotorDriver * motor_cl_r) : IntegratedMag(){
      this->motor_cl_l = motor_cl_l;
      this->motor_cl_r = motor_cl_r;
    }

  private:
    float estimate_angle_on_rpm();

    IRSensorPrediction ir_sens = IRSensorPrediction();
    const ControlledMotorDriver * motor_cl_l;
    const ControlledMotorDriver * motor_cl_r;
    
    // When ir => real angle = ir angle, predicted_angle = magneto angle
    float real_angle = 0.0;
    float predicted_angle = 0.0;

    bool ir_triggered = false;
    bool outside_ir_range = false;

    MagMeterController * IntegratedMag;
};
#endif
