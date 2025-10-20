#include "FSM.h"

void FSM::update(){
  // check if state is ready to change
  if (this->current_state.next_ready){
    this->set_current_state(this->current_state.go_next_state());
  }

  // check if just changed state
  if (this->changed_state){
    this->current_state.enter();
  }

  this->current_state.update();
}
