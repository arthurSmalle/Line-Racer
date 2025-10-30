#ifndef TS_TACHOMETER_H
#define TS_TACHOMETER_H
#include <Arduino.h>
#include <set>
#include "../state machine/State.h"
#include "../motor control/L298NController.h"
#include "../motor control/Tachometer.h"

class TSTachometer : public State{
  public:
    TSTachometer(const float set_point){
      this->set_point = set_point;
    }

  protected:
    bool next_ready = false;

    void enter() override{
      pysical_motor.set_throttle(this->set_point);
      tacho.enable();
    }
    void update()override{
      tacho.calculate_rpm();
      Serial.println("FSMRPM: " + String(tacho.get_rpm()));
    }
    State * go_next_state()override{}

  // make the FSM a friend class of state (allows acces to protected and private fields
  friend class FSM;

  private:
  float set_point;
  static L298NController pysical_motor;
  static Tachometer tacho;
};
L298NController TSTachometer::pysical_motor = L298NController(MOTOR_L1,MOTOR_L2,100);
Tachometer TSTachometer::tacho = Tachometer(TACHO_PIN0A,0);
#endif
