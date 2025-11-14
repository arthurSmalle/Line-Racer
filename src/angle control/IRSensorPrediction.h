#ifndef IRSENSORPREDICTION_H
#define IRSENSORPREDICTION_H
#include <Arduino.h>
#include <cstdint>
class IRSensorPrediction{

  public:
    uint8_t sensitive_to; 
    float get_last_perdiciont(){return this->last_prediction;};
    float predict_angle();
    float get_max_angle();

    void update_ir_readings(){
      ir_array[0] = digitalRead(IR_PIN0);
      ir_array[1] = digitalRead(IR_PIN1);
      #if IR_AMOUNT >= 3
      ir_array[2] = digitalRead(IR_PIN2);
      #endif
    }

    IRSensorPrediction(const uint8_t sensitive_to = HIGH){
      this->sensitive_to = sensitive_to;
      pinMode(IR_PIN0, INPUT); 
      pinMode(IR_PIN1, INPUT); 
      #if IR_AMOUNT >= 3
      pinMode(IR_PIN2, INPUT); 
      #endif
    }
    
  private:
    float last_prediction = 0;
    uint8_t ir_array[IR_AMOUNT] = {0};

};
#endif
