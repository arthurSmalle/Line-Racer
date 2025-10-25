#ifndef FSM_H
#define FSM_H
#include "State.h"

class FSM{
  public:
    void set_current_state(State * const next_state){ 
      free(this->current_state); // remove the old state
      this->current_state = next_state;
      this->changed_state = true;
    }
    void update();

    FSM(State * const initial_state){
      changed_state = true;
      this->current_state = initial_state;
    }

  private:
    State *current_state;
    bool changed_state = false;

};
#endif
