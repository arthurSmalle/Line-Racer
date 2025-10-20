#include "State.h"

class FSM{
  public:
    State get_current_state(){return this->current_state;}

    FSM(const State initial_state){
      this->current_state = initial_state;
    }

  private:
    State current_state;
    State next_state = NULL;
};
