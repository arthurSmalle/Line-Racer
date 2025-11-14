// Prevents overshoot

#ifndef DERIVATIVECONTROLLER_H 
#define DERIVATIVECONTROLLER_H 
#include <Arduino.h>
#include "Controller.h"
class DerivativeController : public Controller{

  public:
    float Kd;

    DerivativeController(float Kd, const float resolution, const float time_component , float * const error_signal, float * const output_signal): Controller(error_signal, output_signal) {
      this->Kd = Kd;
      this->time_component = time_component;
    };

    void set_Kd(const float Kd){
      this->Kd = Kd;
    }

// later obfuscate this function
    void calculate_output() override{
      float rico = (*error_signal - last_measurement) / this->time_component;
      last_measurement = *error_signal;

    if ((*error_signal > this->set_point - this->resolution) && (*error_signal < this->set_point + this->resolution)){
      *this->output_signal = 0;
    } else {
      *this->output_signal = Kd * rico;
    }
    };

  private:
    float last_measurement = 0;
    float time_component;
    float resolution;
};
#endif
