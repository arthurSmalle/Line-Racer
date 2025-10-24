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

    ControlledMotorDriver(const float set_point, const uint8_t motor_pin_1, const uint8_t motor_pin_2, const uint8_t pinA, const uint8_t id, const unsigned long interval = 100, const float Kp = .7,const float Ki = .3, const float Kd = .1): physical_driver(motor_pin_1, motor_pin_2), tachometer(pinA,id, interval), pid(Kp,Ki,Kd, this->error_signal){
      this->set_point = set_point;
      tachometer.enable();
    }

    ControlledMotorDriver(const float set_point, const uint8_t motor_pin_1, const uint8_t motor_pin_2, const uint8_t pinA, const uint8_t pinB,const uint8_t id, const unsigned long interval = 100, const float Kp = .7,const float Ki = .3, const float Kd = .1): physical_driver(motor_pin_1, motor_pin_2), tachometer(pinA, pinB, id, interval), pid(Kp,Ki,Kd, this->error_signal){
      this->set_point = set_point;
      tachometer.enable();
    }

  private:
    float error_signal= 0;
    float rpm; 
    float set_point;

    L298NController physical_driver;
    Tachometer tachometer;
    PIDController pid;
};
#endif
