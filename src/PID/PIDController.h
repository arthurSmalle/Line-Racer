#include "ProportionalController.h"
#include "IntegralController.h"
#include "DerivativeController.h"

class PIDController{
  public:
    ProportionalController PController;
    IntegralController IController;
//    DerivativeController DController;
    float error_signal = 0;
    float output_signal = 0;

    PIDController(const float Kp, const float Ki, const float Kd, float &error_signal) : PController(Kp, error_signal), IController(Ki, error_signal){
      this->error_signal = error_signal;
    };
};
