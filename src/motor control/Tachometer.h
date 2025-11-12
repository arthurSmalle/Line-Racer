// code specificly used for the DFRobot rotary encoder
#ifndef TACHOMETER_H
#define TACHOMETER_H
#include <Arduino.h>

#define MAX_INSTANCE_AMOUNT 2


class Tachometer{
  public:
    void enable();
    void disable();
    
    uint8_t get_id(){return this->id;}
    float get_rpm(){return rpm[this->id];}

    Tachometer(const uint8_t pinA,const uint8_t id){
      if (id < MAX_INSTANCE_AMOUNT && id >= 0){
	this->id = id;
      }
      else {
	this->id = MAX_INSTANCE_AMOUNT; // if invalid id set to max id
      }
      pinsA[this->id] = pinA;
      pinMode(pinA, INPUT);
    }

    Tachometer(const uint8_t pinA,const uint8_t pinB,const uint8_t id){
      if (id < MAX_INSTANCE_AMOUNT && id >= 0){
	this->id = id;
      }
      else {
	this->id = MAX_INSTANCE_AMOUNT; // if invalid id set to max id
      }
      pinsA[this->id] = pinA;
      pinMode(pinA, INPUT);

#if  SINGLE_PIN_TACHO == 0
      pinsB[this->id] = pinB;
      pinMode(pinB, INPUT);
#endif
    }

  private:
    // used as glue function (NOT CLEAN CODE)
    uint8_t id;
    static uint8_t pinsA[MAX_INSTANCE_AMOUNT];

#if SINGLE_PIN_TACHO == 0
    static uint8_t pinsB[MAX_INSTANCE_AMOUNT];
    static volatile bool directions[MAX_INSTANCE_AMOUNT]; // true = forward, false = backward
    static volatile uint8_t last_states[MAX_INSTANCE_AMOUNT]; // last state of the pulse (to check forward or backward movement
#endif

    static volatile unsigned long last_time[MAX_INSTANCE_AMOUNT]; // list time in ms since the last calculation 
    static volatile unsigned long duration[MAX_INSTANCE_AMOUNT]; // time between two pulses
    static volatile float rpm[MAX_INSTANCE_AMOUNT]; // store rpm for each instance

    static void wheel_speed(const uint8_t id);
    static void calculate_rpm(const uint8_t id);
    static void wheel_speed_id0(){wheel_speed(0);};
    static void wheel_speed_id1(){wheel_speed(1);};
};
#endif
