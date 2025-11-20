#ifndef STATE_H
#define STATE_H
#include <Arduino.h>
#include "StatesEnum.h"

class State{
  public:
    State(){}

  protected:
    bool next_ready = false;

    void virtual enter();
    void virtual update();
    StatesEnum virtual go_next_state();

  // make the FSM a friend class of state (allows acces to protected and private fields
  friend class FSM;

  private:
};
#endif
