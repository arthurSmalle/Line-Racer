#ifndef FSM_H
#define FSM_H
#include "State.h"

#include "StatesEnum.h"
// include all posible states
#include "../robot states/RSAdjustOnStraight.h"
#include "../robot states/RSCurve.h"
#include "../robot states/RSSuperCurve.h"
#include "../robot states/RSTokyo.h"
#include "../robot states/RSInit.h"
#include "../robot states/RSEmergency.h"


class FSM{
  public:
    void set_current_state(const StatesEnum stateType);
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
