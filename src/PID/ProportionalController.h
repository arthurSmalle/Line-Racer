#ifndef PROPORTIONALCONTROLLER_H
#define PROPORTIONALCONTROLLER_H
#include "Controller.h"
class ProportionalController : public Controller{

  public:
    float Kp;

    ProportionalController(float Kp, const float &error_signal): Controller(error_signal) {
      this->Kp = Kp;
    };

// later obfuscate this function
    void calculate_output(){
      this->output_signal = Kp * error_signal;
    };
};
#endif
