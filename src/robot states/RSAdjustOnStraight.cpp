#include "RSAdjustOnStraight.h"
#include "RSCurve.h"

// this needs to be defined after the class is delacered (otherwise refrence to RSCurve not found)
inline State * RSAdjustOnStraight::go_next_state(){
  if (curve_detected){
    return new RSCurve(); 
  }
}
