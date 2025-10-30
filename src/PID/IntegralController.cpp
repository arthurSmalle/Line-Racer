#include "IntegralController.h"
#ifdef DEBUG
#include <Arduino.h>
#endif

void IntegralController::calculate_output_narrow_scope(){
  // save error_signal to the integrator list
  integrator_data[integrator_list_index] = *error_signal;
  // move the index in the list
  integrator_list_index++;
    if (integrator_list_index >= INTEGRATOR_SIZE){ integrator_list_index = 0;}
      // reset output
      this->output_signal = 0;
      // calculate the integral
      for (int i = 0; i < INTEGRATOR_SIZE; i++){
	*this->output_signal += integrator_data[i];
      }

      *this->output_signal = Ki * *output_signal;
}


void IntegralController::calculate_output_wide_scope(){
    // apply clipping to the signal (avoid the integral_value from rising when steady state error)
    if ((*error_signal > this->set_point - this->resolution) && (*error_signal < this->set_point + this->resolution))
    {
      integral_value = 0;
      *this->output_signal = 0;
#ifdef DEBUG
      Serial.println("CLIPPING");
#endif
    } else{
      integral_value += *error_signal;
      *this->output_signal = Ki* integral_value;
    }
}
