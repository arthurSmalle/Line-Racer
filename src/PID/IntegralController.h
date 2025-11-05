// Prevents steady state error
#ifndef INTEGRALCONTROLLER_H
#define INTEGRALCONTROLLER_H
#include "Controller.h"
#define INTEGRATOR_SIZE 20

enum IntegralScope {NARROW, WIDE};

class IntegralController : public Controller{

  public:
    float Ki;
    IntegralScope scope = WIDE;
    void set_resolution(const float resolution){this->resolution = resolution;}

    IntegralController(const float Ki, const float resolution, float * const error_signal, float * const output_signal, const IntegralScope scope = WIDE): Controller(error_signal, output_signal) {
      this->scope = scope;
      this->Ki = Ki;
      this->resolution = resolution;
      this->set_point = 0;
    };
    
    IntegralController(const float Ki, const float resolution, const float set_point,float * const error_signal, float * const output_signal, const IntegralScope scope = WIDE): IntegralController( Ki, resolution, error_signal, output_signal,scope ) {
      this->set_point = set_point;
    }

// later obfuscate these functions
    void calculate_output(){
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
    float resolution;
  
    // calculate the integral of only a small portion of sensor readings
    void calculate_output_narrow_scope();

  // calculate the integral of all sensor readings
  void calculate_output_wide_scope();
    
};
#endif
