#include "StateGlue.h"
#include "RSAdjustOnStraight.h"
#include "RSCurve.h"

class RSAdjustOnStraight;
class RSCurve;

State * StateGlue::go_next_state(){
  switch (this->next_state) {
  case StatesEnum::AdjustOnStraight:
    return new RSAdjustOnStraight();
  break;
  case StatesEnum::Curve:
    return new RSCurve();
  break;
  default:
  // TODO MAKE INIT FUNCTION
    return new RSCurve();
  }
}
