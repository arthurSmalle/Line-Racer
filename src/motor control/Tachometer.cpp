#include "Tachometer.h"
#include <Arduino.h>
#define MILLIS_IN_MINUTE 3600
#define GEAR_RATIO 120

// initialse the static var
uint8_t Tachometer::pinsA[MAX_INSTANCE_AMOUNT] = {0};
uint8_t Tachometer::pinsB[MAX_INSTANCE_AMOUNT] = {0};
volatile unsigned long Tachometer::duration[MAX_INSTANCE_AMOUNT] = {0};
volatile bool Tachometer::directions[MAX_INSTANCE_AMOUNT] = {0}; // true = forward, false = backward
volatile uint8_t Tachometer::last_states[MAX_INSTANCE_AMOUNT] = {0};

void Tachometer::calculate_rpm(){}

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
