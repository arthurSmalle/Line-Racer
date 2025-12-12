#ifndef ANGLE_CONTROLLER_H
#define ANGLE_CONTROLLER_H
#include "IRSensorPrediction.h"
#include "../motor control/ControlledMotorDriver.h"
#include "angle control/MagMeterController.h"
#ifdef ARDUINO_NANO_BLE
#ifdef USE_IMU
#include "LSM9DS1Controller.h"
#endif
#endif ARDUINO_NANO_BLE

class AngleController{
  public:
#ifdef USE_IMU
    // DEBUGING FUNCTION
    void get_IMU_DATA(float &x, float &y, float &z){
      this->IntegratedMag->get_measured_data(x,y,z);
    }
    void get_zp_data(float &x, float &y, float &z){
      this->IntegratedMag->get_zp_data(x, y, z);
    }
#endif
    void update(); // update all the measurements and calculations
    float get_real_angle(){return this->real_angle;} // get the "real angle" determined by one of the sensors on runtime
    // TODO implement automatic balancing of real and predicted_angle (based on time since laste measurement)
    float get_predicted_angle(){return this->predicted_angle;} // get a estimate of the angle determined by calculations and tests before runtime
    unsigned long get_time_since_real_measured(); // get time since the real angle was measured (to avoid using "old" data)
    bool get_is_outside_ir_range(); // get if the real angle is outside the infrared sensor range (meaning the robot goes off track!)
    bool get_ir_triggered(){return this->ir_triggered;}
    void emergency_flip(){this->real_angle *= -1;}

#ifdef USE_IMU
    // MAGMETER FUNCTIONS //
    void set_mag_zp(const int measurements); // WARNING THIS WILL STALL THE PROGRAM
    void set_mag_angle_ref(const int measurements,float rad = 0); // WARNING THIS WILL STALL THE PROGRAM
    bool get_imu_status(){return this->could_init_imu;}
#endif

    AngleController(const ControlledMotorDriver * motor_cl_l, const ControlledMotorDriver * motor_cl_r){
#ifdef USE_IMU
      this->IntegratedMag = new LSM9DS1Controller();
#endif
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
    
#ifdef USE_IMU
    // MAGMETER FUNCTIONS //
    MagMeterController * IntegratedMag;
    void get_average_mag_data(float &x,float &y,float &z, int measurements); // WARNING THIS WILL STALL THE PROGRAM
    bool could_init_imu = false;
#endif
};
#endif
