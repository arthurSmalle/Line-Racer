// Prevents steady state error
#ifndef INTEGRALCONTROLLER_H
#include "Controller.h"
#define INTEGRATOR_SIZE 20

class IntegralController : Controller{

  public:
    float Ki;

    IntegralController(float Ki, float &error_signal): Controller(error_signal) {
      this->Ki = Ki;
    };

// later obfuscate these functions

  // calculate the integral of only a small portion of sensor readings
    void calculate_output_narrow_scope(){
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
    };

  // calculate the integral of all sensor readings
  void calculate_output_wide_scope(){
    integral_value += error_signal;
    this->output_signal = Ki* integral_value;
  }

  private:
    // maybe replace with ring structure?
    char integrator_list_index = 0;
    float integrator_data[INTEGRATOR_SIZE] = {0}; // TODO REMOVE MAGIC NUMBER
    float integral_value = 0;
    
};
#endif
