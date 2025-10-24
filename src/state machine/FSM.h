#ifndef FSM_H
#define FSM_H
#include "State.h"

class FSM{
  public:
    void set_current_state(const State next_state){ 
      this->current_state = next_state;
      this->changed_state = true;
    }
    void update();

    FSM(const State initial_state){
      this->current_state = initial_state;
    }

  private:
    State current_state;
    bool changed_state = false;

};
#endif
