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
      State *next_state;
      switch (stateType){
	State * next_state;
	case StatesEnum::AdjustOnStraight:
	  next_state = new RSAdjustOnStraight();
	  this->current_state_type = AdjustOnStraight;
	  break;
	case StatesEnum::Curve:
	   next_state = new RSCurve();
	   this->current_state_type = Curve;
	   break;
	case StatesEnum::LostLine:
//	   next_state = new RSLineLost();
	   this->current_state_type = LostLine;
	   break;
	case StatesEnum::Triangle:
	   next_state = new RSTriangle();
	   this->current_state_type = Triangle;
	   break;
	default:
//	   next_state = new RSInit();
	   this->current_state_type = Init;
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
    StatesEnum current_state_type = Init;
    bool changed_state = false;

};
#endif
