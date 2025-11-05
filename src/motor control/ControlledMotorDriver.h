#ifndef CONTROLLEDMOTORDRIVER_H
#define CONTROLLEDMOTORDRIVER_H
#include "L298NController.h"
#include "Tachometer.h"
#include "../PID/PIDController.h"


class ControlledMotorDriver{
  public:
    //******************//
    // setter functions //
    //******************//

    void set_set_point(const float set_point){this->set_point = set_point;} // set point in rpm
    void set_clock_wise(bool clk){this->physical_driver.clockwise = clk;};
    void set_update_time(const unsigned long update_time){this->update_time = update_time;} // modify the update time
    void set_tachometer_interval_time(const unsigned long interval){this->tachometer.set_interval(interval);}
									 
    //******************//
    // getter functions //
    //******************//

    float get_rpm(){return this->rpm;}

    //*****************************//
    // general operation functions //
    //*****************************//

    void update();

    void enable();
    void stop();

    // note: update_time is used as timecomponent for D controller
    ControlledMotorDriver(const float set_point,  const unsigned long update_time, const uint8_t motor_pin_1, const uint8_t motor_pin_2, const uint8_t pinA, const uint8_t id, const float Kp = .7,const float Ki = .3, const float Kd = .1, const float resolution = 0.1): physical_driver(motor_pin_1, motor_pin_2), tachometer(pinA,id), pid(Kp,Ki,Kd, resolution, update_time,set_point, this->error_signal, this->output_signal){
      this->set_point = set_point;
      this->update_time = update_time;
      tachometer.enable();
    }

  private:
    float error = 0;
    float output = 0;
    float *error_signal = &error;
    float *output_signal = &output;
    float rpm; 
    float set_point;

    unsigned long update_time = 150;
    unsigned long last_calculation = 0;

    L298NController physical_driver;
    Tachometer tachometer;
    PIDController pid;
};
#endif
