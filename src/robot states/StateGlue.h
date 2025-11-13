#ifndef  STATE_GLUE_H
#define STATE_GLUE_H
#include "state machine/State.h"
#include "StatesEnum.h"

class StateGlue : public State{
  public:
    StateGlue(StatesEnum next_state = StatesEnum::Init){
      this->next_state = next_state;
    }
  protected:
    void enter() override{
      this->next_ready = true;
    }

    State * go_next_state() override;
  private:
    StatesEnum next_state;
};
#endif
