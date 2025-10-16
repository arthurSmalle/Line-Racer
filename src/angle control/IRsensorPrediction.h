#ifndef IRSENSORPREDICTION_H
#define IRSENSORPREDICTION_H
#include <Arduino.h>
class IRSensorPrediction{

  public:
    float get_last_perdiciont(){return this->last_prediction;};
    IRSensorPrediction(){};
  
  private:
    float last_prediction = 0;
    uint8_t ir_array[IR_AMOUNT] = {0};

    void get_ir_readings(){
      ir_array[0] = digitalRead(IR_PIN0);
      ir_array[1] = digitalRead(IR_PIN1);
      #if IR_AMOUNT >= 3
      ir_array[2] = digitalRead(IR_PIN2);
      #endif
    }

  // TODO continue working here  
  #if IR_AMOUNT == 2
  public:
    float predict_angle(){
      float prediction = 0;
      if (ir_array[0] == HIGH){
	 prediction= -1 * tan(SYMM_TO_IR/WHEELS_TO_IR);
	last_prediction = prediction;
      } 
      else if (ir_array[1] == HIGH){
	prediction = tan(SYMM_TO_IR/WHEELS_TO_IR);
	last_prediction = prediction;
      }

      return prediction;
      }
    private:
  #endif

  #if IR_AMOUNT == 3
  // TEMP CODE REWORK THIS LATER
  public:
    float predict_angle(){
      if (ir_array[1] && ir_array[2] == LOW){
	last_prediction = 0;
	return last_prediction;

      } else if ((ir_array[1] xor ir_array[2]) == HIGH){

	float prediciton = (-1*ir_array[2]) * tan(SYMM_TO_IR/WHEELS_TO_IR);
	last_prediction = prediciton;
	return last_prediction;
      } 
      // other casses
      else {
	return 0;
      }
    }

  private:
  #endif // end 3 ir led logic
};
#endif
