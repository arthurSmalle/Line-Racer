#include <Arduino.h>
#include "FSM.h"
#include "state machine/StatesEnum.h"

void FSM::update(){
  // check if state is ready to change
  if ((this->current_state)->next_ready){
    this->set_current_state((this->current_state)->go_next_state());
    this->changed_state = true;
  }

  // check if just changed state
  if (this->changed_state){
    (this->current_state)->enter();
    this->changed_state = false;
  }

  (this->current_state)->update();
}

void FSM::set_current_state(const StatesEnum stateType){ 
      free(this->current_state); // remove the old state
      State *next_state;
      switch (stateType){
	case StatesEnum::AdjustOnStraight:
	  next_state = new RSAdjustOnStraight();
	  this->current_state_type = AdjustOnStraight;
	  break;
	case StatesEnum::Curve:
	   next_state = new RSCurve();
	   this->current_state_type = Curve;
	   break;
	case StatesEnum::SuperCurve:
	   next_state = new RSSuperCurve();
	   this->current_state_type = SuperCurve;
	   break;
	case StatesEnum::Tokyo:
	   next_state = new RSTokyo();
	   this->current_state_type = Tokyo;
	   break;
	default:
	   next_state = new RSInit(StatesEnum::AdjustOnStraight);
	   this->current_state_type = Init;
      }
      this->current_state = next_state;
      this->changed_state = true;
    }
