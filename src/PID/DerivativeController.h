// Prevents overshoot

#ifndef DERIVATIVECONTROLLER_H 
#define DERIVATIVECONTROLLER_H 
#include <Arduino.h>
#include "Controller.h"
class DerivativeController : public Controller{

  public:
    float Kd;

    DerivativeController(float Kd, const float &error_signal): Controller(error_signal) {
      this->Kd = Kd;
    };

// later obfuscate this function
    void calculate_output(){
      unsigned long new_measure_time = millis();
      float rico = (error_signal - last_measurement) / (new_measure_time - last_measure_time);
      last_measurement = error_signal;
      last_measure_time = new_measure_time;

      this->output_signal = Kd * rico;
    };

  private:
    unsigned long last_measure_time = 0;
    float last_measurement = 0;
};
#endif
