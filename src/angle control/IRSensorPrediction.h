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
  public:
    float predict_angle();
  private:
};
#endif
