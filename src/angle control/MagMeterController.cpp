#include "MagMeterController.h"

float MagMeterController::get_angle_to_zero(){
  if (!angle_ref_set || !zp_set){
    return 0;
  } else {
    if (!angle_to_tan_scale_set){
      calculate_angle_to_tan_scale();
    }
    return tan(x_zp - x/y_zp - y) * angle_to_tan_scale;
  }
}
