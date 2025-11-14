#ifndef FSM_H
#define FSM_H
#include "State.h"

#include "StatesEnum.h"
// include all posible states
#include "../robot states/RSAdjustOnStraight.h"
#include "../robot states/RSCurve.h"
#include "../robot states/RSLineLost.h"
#include "../robot states/RSTriangle.h"

class FSM{
  public:
    void set_current_state(const StatesEnum stateType){ 
      free(this->current_state); // remove the old state
      switch (stateType){
	State * next_state;
	case StatesEnum::AdjustOnStraight:
	  next_state = new RSAdjustOnStraight();
	  break;
	case StatesEnum::Curve:
	   next_state = new RSCurve();
	   break;
	case StatesEnum::LostLine:
	   next_state = new RSLineLost();
	   break;
      }
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
