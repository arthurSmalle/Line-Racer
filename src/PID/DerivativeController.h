// Prevents overshoot

#ifndef DERIVATIVECONTROLLER_H 
#include "Controller.h"
class DerivativeController : Controller{

  public:
    float Kd;

    DerivativeController(float Kd, float &error_signal): Controller(error_signal) {
      this->Kd = Kd;
    };

// later obfuscate this function
    void calculate_output(){
      this->output_signal = Kd * error_signal;
    };
};
#endif
