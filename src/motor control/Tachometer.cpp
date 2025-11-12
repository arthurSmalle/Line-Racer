#include "Tachometer.h"
#include <Arduino.h>
#define MICROS_IN_MINUTE 60000000
#define GEAR_RATIO 120 
#define READ_RESOLUTION 16
#define MICROS_TILL_STAGNATE 30000

// initialse the static var
uint8_t Tachometer::pinsA[MAX_INSTANCE_AMOUNT] = {0};
#if SINGLE_PIN_TACHO == 0
uint8_t Tachometer::pinsB[MAX_INSTANCE_AMOUNT] = {0};
volatile bool Tachometer::directions[MAX_INSTANCE_AMOUNT] = {0}; // true = forward, false = backward
volatile uint8_t Tachometer::last_states[MAX_INSTANCE_AMOUNT] = {0};
#endif
volatile unsigned long Tachometer::last_time[MAX_INSTANCE_AMOUNT]; // list time in ms since the last calculation 
volatile unsigned long Tachometer::duration[MAX_INSTANCE_AMOUNT] = {0};
volatile float Tachometer::rpm[MAX_INSTANCE_AMOUNT] = {0};

// get rpm and check if the wheel is not standing still
float Tachometer::get_rpm(){
  unsigned long currrent_time = micros();
  unsigned long time_diff = currrent_time - last_time[id];
  this->time_diff = time_diff;

  // check if wheel has rotated recently, otherwise set RPM to 0
   if (time_diff > MICROS_TILL_STAGNATE){
    rpm[this->id] = 0;
  }
  return rpm[this->id];
}

// calculate rpm in function of amount of rotations
void Tachometer::calculate_rpm(const uint8_t id){
  unsigned long currrent_time = micros();

  unsigned long time_diff = currrent_time - last_time[id];
  rpm[id] =  (1/float(GEAR_RATIO))* (float(MICROS_IN_MINUTE) / time_diff);
  last_time[id] = currrent_time;
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
  // increment the wheel spin counter, when certain value check time diff
  duration[id]++;
  if (duration[id] >= READ_RESOLUTION){
    calculate_rpm(id);
    duration[id] = 0;
  }
}
