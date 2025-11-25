#ifdef ARDUINO_NANO_BLE
#ifndef RS_BLE_H
#define RS_BLE_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>

class RSBLE : public RobotState{
  public:
    RSBLE(){}

  protected:
    void enter() override;

    // keep looping
    void update() override;
    StatesEnum go_next_state() override{}
};

#endif
#endif
