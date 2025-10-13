#include "Tachometer.h"
#include <Arduino.h>
#define MILLIS_IN_MINUTE 60000
#define GEAR_RATIO 120

// initialse the static var
uint8_t Tachometer::pinsA[MAX_INSTANCE_AMOUNT] = {0};
uint8_t Tachometer::pinsB[MAX_INSTANCE_AMOUNT] = {0};
volatile unsigned long Tachometer::last_time[MAX_INSTANCE_AMOUNT] = {0}; // list time in ms since the last pulse 
volatile unsigned long Tachometer::duration[MAX_INSTANCE_AMOUNT] = {0};
volatile uint8_t Tachometer::sample_counter[MAX_INSTANCE_AMOUNT] = {0}; // keeps count for when to sample
volatile bool Tachometer::directions[MAX_INSTANCE_AMOUNT] = {0}; // true = forward, false = backward
volatile uint8_t Tachometer::last_states[MAX_INSTANCE_AMOUNT] = {0};

void Tachometer::calculate_rpm(){
#ifdef DEBUG
  Serial.println("=== TACHODEBUG ===");
  Serial.println("duration:");
  Serial.print(duration[id]);
  Serial.println("duration*1000:" + String(duration[this->id]*1000));
  Serial.print(duration[id]*1000);
  Serial.println("rpm:" + String(this->rpm));
#endif
  this->rpm =  float(MILLIS_IN_MINUTE * TACHO_SAMPLE_SIZE) / (GEAR_RATIO * duration[this->id] * 2);  // times 2 because makes 2 measurements for each rotation
}

void Tachometer::enable(){
  pinMode(Tachometer::pinsB[this->id], INPUT);  
  if (this->id == 0){
    attachInterrupt(digitalPinToInterrupt(Tachometer::pinsA[this->id]), wheel_speed_id0, CHANGE);
  } else if (this->id == 1){
    attachInterrupt(digitalPinToInterrupt(Tachometer::pinsA[this->id]), wheel_speed_id1, CHANGE);
  }
}

void Tachometer::disable(){
    detachInterrupt(digitalPinToInterrupt(Tachometer::pinsA[this->id]));
}


void Tachometer::wheel_speed(const uint8_t id){
  sample_counter[id]++;
  if (sample_counter[id] > int(TACHO_SAMPLE_SIZE)){
   // check the speed of the rotation
   unsigned long current_time = millis();
   duration[id] = current_time - last_time[id];
   last_time[id] = current_time;
   sample_counter[id] = 0;
  }

  // check the direction of the rotation
  uint8_t current_state = digitalRead(pinsA[id]);
  if ((last_states[id] == LOW) && (current_state == HIGH)){
    uint8_t  val = digitalRead(pinsB[id]);
    if (val == LOW && directions[id]){
      directions[id] = false; // reverse rotation detected
    } else if (val == HIGH && !directions[id]){
      directions[id] = true;
    }
  }
  last_states[id] = current_state;
  // if (!directions[id]){
  //   duration[id]++;
  // } else {
  //   duration[id]--;
  // }
}
