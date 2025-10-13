#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H
#include <Arduino.h>
#include "PID/Controller.h"
#include "ProportionalController.h"
#include "IntegralController.h"
#include "DerivativeController.h"

class PIDController: public Controller{
  public:
    PIDController(const float Kp, const float Ki, const float Kd, const float &error_signal): Controller(error_signal), PController(Kp, error_signal), IController(Ki, error_signal), DController(Kd, error_signal){
      this->error_signal = error_signal;
    };
    
    void calculate_output(){
	this->PController.calculate_output(); 
	this->IController.calculate_output();
	this->DController.calculate_output();

	#ifdef DEBUG
	  Serial.println("P: " + String(this->PController.get_output_signal()));
	  Serial.println("I: " + String(this->IController.get_output_signal()));
	  Serial.println("D: " + String(this->DController.get_output_signal()));
	#endif

	this->output_signal = 
	  this->PController.get_output_signal() +
	  this->IController.get_output_signal() +
	  this->DController.get_output_signal();
    }
    
    void set_error_signal(const float &error_signal) override{
      this->error_signal = error_signal;
      this->PController.set_error_signal(error_signal);
      this->IController.set_error_signal(error_signal);
      this->DController.set_error_signal(error_signal);
    }
  private: 
    ProportionalController PController;
    IntegralController IController;
    DerivativeController DController;

    // maybe implement a set point and  compute function? (removing this from the main function)
};
#endif
