#ifndef TS_TACHOMETER_H
#define TS_TACHOMETER_H
#include <Arduino.h>
#include "../state machine/State.h"
#include "../motor control/L298NController.h"
#include "../motor control/Tachometer.h"
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
      pysical_motor.set_throttle(15);
      tacho.enable();
    }
    void update()override{
      this->rpm = tacho.get_rpm();
//      pid.calculate_output();
      tacho_error = this->set_point - rpm;
      unsigned long time_diff = tacho.get_last_time();
      Serial.println("====FSM Debug====");
      Serial.println("FSMRPM: " + String(rpm));
      Serial.println("time_diff" + String(time_diff));
      delay(100);
    }
    State * go_next_state()override{}

  // make the FSM a friend class of state (allows acces to protected and private fields
  friend class FSM;

  private:
  float set_point = 0;
  float tacho_error = 0;
  float tacho_output = 0;
  unsigned long tacho_interval;
  int test_interval;
//  PIDController pid = PIDController(.5, .3, .4, 0.01, .1, set_point, &tacho_error, &tacho_output);
  float rpm = 0;

  static L298NController pysical_motor;
  static Tachometer tacho;
};
L298NController TSTachometer::pysical_motor = L298NController(MOTOR_L1,MOTOR_L2,100);
Tachometer TSTachometer::tacho = Tachometer(TACHO_PIN0A,0);
#endif
