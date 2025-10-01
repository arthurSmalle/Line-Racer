#include "ProportionalController.h"
#include "IntegralController.h"
#include "DerivativeController.h"

class PIDController{
  public:
    float Kp;
    float Ki;
    float Kd;
    float error_signal = 0;
    float output_signal = 0;

    PIDController(const float Kp, const float Ki, const float Kd, float &error_signal, float &output_signal){
      this->Kp = Kp;
      this->Ki = Ki;
      this->Kd = Kd;
      this->error_signal = error_signal;
      this->output_signal = output_signal;
    };
};
