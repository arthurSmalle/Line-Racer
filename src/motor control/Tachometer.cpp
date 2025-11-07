#include "Tachometer.h"
#include <Arduino.h>
#define MICROS_IN_MINUTE 60000000
#define GEAR_RATIO 120 
#define READ_RESOLUTION 16

// initialse the static var
uint8_t Tachometer::pinsA[MAX_INSTANCE_AMOUNT] = {0};
#if SINGLE_PIN_TACHO == 0
uint8_t Tachometer::pinsB[MAX_INSTANCE_AMOUNT] = {0};
volatile bool Tachometer::directions[MAX_INSTANCE_AMOUNT] = {0}; // true = forward, false = backward
volatile uint8_t Tachometer::last_states[MAX_INSTANCE_AMOUNT] = {0};
#endif
volatile unsigned long Tachometer::duration[MAX_INSTANCE_AMOUNT] = {0};
volatile uint8_t Tachometer::sample_counter[MAX_INSTANCE_AMOUNT] = {0}; // keeps count for when to sample

// THERE SHOULD BE A CONSIDIRABLE DELAY BETWEEN CALLING THIS FUNCTION PERIODICLY
void Tachometer::calculate_rpm(const bool ignore_interval){
  unsigned long currrent_time = micros();

  // chech if enough time passed to do calculation or if the interval should be ignored
  if (((currrent_time - this->last_calculation) > this->interval) || ignore_interval){
  float rotations = float(duration[id]) / (GEAR_RATIO * READ_RESOLUTION);
  unsigned long passed_time = currrent_time - last_calculation;
  rpm = (rotations / float(passed_time)) * MICROS_IN_MINUTE;
//#ifdef DEBUG
  Serial.println("=== TACHODEBUG ===");
  Serial.println("duration: " + String(duration[id]));
  Serial.println("rotations: " + String(rotations));
  Serial.println("passed_time: " + String(passed_time));
  Serial.println("rpm: " + String(this->rpm));
  Serial.println("ignore_interval: " + String(ignore_interval));
//#endif
  this->last_calculation = currrent_time;
  duration[id] = 0;
  }
}

void Tachometer::enable(){
#if SINGLE_PIN_TACHO == 0
  pinMode(Tachometer::pinsB[this->id], INPUT);
#endif

  // assign the interrupt pins to the correct glue function
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
  // sample_counter[id]++;
  // if (sample_counter[id] > int(TACHO_SAMPLE_SIZE)){
  //  // check the speed of the rotation
  //  unsigned long current_time = micros();
  //  duration[id] = current_time - last_time[id];
  //  last_time[id] = current_time;
  //  sample_counter[id] = 0;
  // }

  // check the direction of the rotation
#if SINGLE_PIN_TACHO == 0
  uint8_t current_state = digitalRead(pinsA[id]);
  if ((last_states[id] == LOW) && (current_state == HIGH)){
    uint8_t  val = digitalRead(pinsB[id]);
    if (val == LOW && directions[id]){
      directions[id] = false; // reverse rotation detected
    } else if (val == HIGH && !directions[id]){
      directions[id] = true;
    }
  }
#endif
  duration[id]++;
  // last_states[id] = current_state;
  // if (!directions[id]){
  //   duration[id]++;
  // } else {
  //   duration[id]--;
  // }
}
