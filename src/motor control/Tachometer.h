// code specificly used for the DFRobot rotary encoder
#ifndef TACHOMETER_H
#define TACHOMETER_H
#include <Arduino.h>

#define MAX_INSTANCE_AMOUNT 2


class Tachometer{
  public:
    void calculate_rpm();
    uint8_t get_id(){return this->id;};
    float get_rpm(){return this->rpm;}
    void enable();
    void disable();

    Tachometer(const uint8_t pinA,const uint8_t pinB,const uint8_t id){
      if (id < MAX_INSTANCE_AMOUNT && id >= 0){
	this->id = id;
      }
      else {
	this->id = MAX_INSTANCE_AMOUNT; // if invalid id set to max id
      }
      pinsA[this->id] = pinA;
      pinsB[this->id] = pinB;
    }

  private:
    float rpm = 0;
    // used as glue function (NOT CLEAN CODE)
    uint8_t id;
    static uint8_t pinsA[MAX_INSTANCE_AMOUNT];
    static uint8_t pinsB[MAX_INSTANCE_AMOUNT];

    static volatile unsigned long last_time[MAX_INSTANCE_AMOUNT]; // list time in ms since the last pulse 
    static volatile unsigned long duration[MAX_INSTANCE_AMOUNT]; // time between two pulses
    static volatile uint8_t sample_counter[MAX_INSTANCE_AMOUNT]; // keeps count for when to sample

    static volatile bool directions[MAX_INSTANCE_AMOUNT]; // true = forward, false = backward
    static volatile uint8_t last_states[MAX_INSTANCE_AMOUNT]; // last state of the pulse (to check forward or backward movement

    static void wheel_speed(const uint8_t id);
    static void wheel_speed_id0(){wheel_speed(0);};
    static void wheel_speed_id1(){wheel_speed(1);};
};
#endif
