// Prevents steady state error
#ifndef INTEGRALCONTROLLER_H
#include "Controller.h"
#define INTEGRATOR_SIZE 20

enum IntegralScope {NARROW, WIDE};

class IntegralController : Controller{

  public:
    float Ki;
    IntegralScope scope = NARROW;

    IntegralController(const float Ki, const float &error_signal, const IntegralScope scope): Controller(error_signal) {
      this->scope = scope;
      this->Ki = Ki;
    };

// later obfuscate these functions
    void calculate_output(const IntegralScope){
      if (this->scope == NARROW){
	calculate_output_narrow_scope();
      }
      else {
	calculate_output_wide_scope();
      }
    }

  private:
    // maybe replace with ring structure?
    char integrator_list_index = 0;
    float integrator_data[INTEGRATOR_SIZE] = {0}; // TODO REMOVE MAGIC NUMBER
    float integral_value = 0;
  
    // calculate the integral of only a small portion of sensor readings
    void calculate_output_narrow_scope();

  // calculate the integral of all sensor readings
  void calculate_output_wide_scope();
    
};
#endif
