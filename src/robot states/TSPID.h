#ifndef TSPID_H
#define TSPID_H
#include <Arduino.h>
#include "../state machine/State.h"
#include "PID/PIDController.h"

class TSPID :  public State{
  public:
    TSPID(){}

  protected:
    void virtual enter(){}

    void virtual update(){
      while ((output_signal > 0 + resolution) || (output_signal < 0 - resolution)){
        pid.calculate_output();
        error_signal -=  output_signal /100;
        Serial.println("output pid: " +String(pid.get_output_signal()));
        Serial.println("output: " +String(output_signal));
        Serial.println("error_signal:" + String(error_signal));
        delay(100);
        counter++;
	}
      Serial.println("PID REACHED STEADY STATE AFTER " + String(counter) + " LOOPS");
      delay(3000);
    }
    State virtual * go_next_state(){}

  private:

    int counter = 0;
    float error_signal =100;
    float output_signal=1;
    float resolution = 0.1;
    PIDController pid = PIDController(1, 0.3, 0, resolution, 1, 0, &error_signal, &output_signal);
};

#endif
