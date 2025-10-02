#ifndef IRSENSORPREDICTION_H
#define IRSENSORPREDICTION_H
#include <Arduino.h>
class IRSensorPrediction{

  public:
    float get_last_perdiciont(){return this->last_prediction;};
    IRSensorPrediction(){};
  
  private:
    float last_prediction = 0;

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
    }

  private:
    uint8_t ir_array[3] = {0};

    void get_ir_readings(){
      ir_array[0] = digitalRead(IR_PIN0);
      ir_array[1] = digitalRead(IR_PIN1);
      ir_array[2] = digitalRead(IR_PIN2);
    }

  #endif // end 3 ir led logic
};
#endif
