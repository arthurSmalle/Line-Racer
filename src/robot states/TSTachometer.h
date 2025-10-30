#ifndef TS_TACHOMETER_H
#define TS_TACHOMETER_H
#include <Arduino.h>
#include "../state machine/State.h"
#include "../motor control/L298NController.h"
#include "../motor control/Tachometer.h"
#include "../PID/BinarySearch.h"
#include "../PID/PIDController.h"


class TSTachometer : public State{
  public:
    TSTachometer(const float set_point, unsigned long tacho_interval, int test_interval){
      this->set_point = set_point;
      this->tacho_interval = tacho_interval;
      this->test_interval = test_interval;
    }

  protected:
    bool next_ready = false;

    void enter() override{
      pysical_motor.set_throttle(30);
      tacho.enable();
      tacho.set_interval(this->tacho_interval);
    }
    void update()override{
      tacho.calculate_rpm();
      this->rpm = tacho.get_rpm();
      pid.set_error_signal(this->set_point - this->rpm);
      pid.calculate_output();
      float output_signal = pid.get_output_signal();
      tacho.set_interval(tacho.get_interval() + output_signal);
      Serial.println("FSMRPM: " + String(rpm));
      Serial.println("interval:" + String(tacho.get_interval()));
    }
    State * go_next_state()override{}

  // make the FSM a friend class of state (allows acces to protected and private fields
  friend class FSM;

  private:
  float set_point;
  unsigned long tacho_interval;
  int test_interval;
  PIDController pid = PIDController(.8, .2, .1, rpm);
  float rpm = 0;

  static L298NController pysical_motor;
  static Tachometer tacho;
};
L298NController TSTachometer::pysical_motor = L298NController(MOTOR_L1,MOTOR_L2,100);
Tachometer TSTachometer::tacho = Tachometer(TACHO_PIN0A,0);
#endif
