#include "IRSensorPrediction.h"
#include <Arduino.h>

float IRSensorPrediction::predict_angle()
#if IR_AMOUNT == 2
{
      float prediction = 0;

      if (ir_array[0] == this->sensitive_to){
	 prediction=  tan(SYMM_TO_IR/WHEELS_TO_IR);
	last_prediction = prediction;
#ifdef DEBUG
Serial.println("+++++++++++++++++");
Serial.println("LEFT SENSOR TRIGGERED");
Serial.println("+++++++++++++++++");
#endif
      }

      if (ir_array[1] == this->sensitive_to){
	prediction = -1 *tan(SYMM_TO_IR/WHEELS_TO_IR);
	last_prediction = prediction;
#ifdef DEBUG
Serial.println("+++++++++++++++++");
Serial.println("RIGHT SENSOR TRIGGERED");
Serial.println("+++++++++++++++++");
#endif
      }

      return prediction;
}
#endif
#if IR_AMOUNT == 3
{
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
#endif
float IRSensorPrediction::get_max_angle()
#if IR_AMOUNT == 2
{
	 return tan(SYMM_TO_IR/WHEELS_TO_IR);
}
#endif
#if IR_AMOUNT == 3
{} //TODO IMPLEMENT THIS LATER
#endif
