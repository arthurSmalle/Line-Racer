#include "IntegralController.h"

void IntegralController::calculate_output_narrow_scope(){
  // save error_signal to the integrator list
  integrator_data[integrator_list_index] = error_signal;
  // move the index in the list
  integrator_list_index++;
    if (integrator_list_index >= INTEGRATOR_SIZE){ integrator_list_index = 0;}
      // reset output
      this->output_signal = 0;
      // calculate the integral
      for (int i = 0; i < INTEGRATOR_SIZE; i++){
	this->output_signal += integrator_data[i];
      }

      this->output_signal = Ki * output_signal;
}


void IntegralController::calculate_output_wide_scope(){
    integral_value += error_signal;
    this->output_signal = Ki* integral_value;
}
