#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H
#include <Arduino.h>
#include "PID/Controller.h"
#include "ProportionalController.h"
#include "IntegralController.h"
#include "DerivativeController.h"

class PIDController: public Controller{
  public:
    PIDController(const float Kp, const float Ki, const float Kd, const float resolution, const float time_component, const float set_point, float * const error_signal, float * const output_signal): Controller(error_signal, output_signal), PController(Kp, error_signal, &p_output), IController(Ki, resolution, set_point, error_signal, &i_output), DController(Kd,resolution, time_component, error_signal, &d_output){
      this->error_signal = error_signal;
    };
    
    void calculate_output() override{
	this->PController.calculate_output(); 
	this->IController.calculate_output();
	this->DController.calculate_output();
	
	*this->output_signal = p_output + i_output + d_output;

	#ifdef DEBUG
	  Serial.println("P: " + String(this->PController.get_output_signal()));
	  Serial.println("I: " + String(this->IController.get_output_signal()));
	  Serial.println("D: " + String(this->DController.get_output_signal()));
	#endif
    }
    
    void set_set_point(const float set_point) override{
      IController.set_set_point(set_point);
      this->set_point = set_point;
    }

    void update(){
      float temp_error = *this->error_signal;
      *this->error_signal = this->set_point - *this->error_signal;
      calculate_output();
      *this->error_signal = temp_error;
    }

  private: 
    ProportionalController PController;
    float p_output = 0;
    IntegralController IController;
    float i_output = 0;
    DerivativeController DController;
    float d_output = 0;

    // maybe implement a set point and  compute function? (removing this from the main function)
};
#endif
