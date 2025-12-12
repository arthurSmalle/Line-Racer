#ifndef RS_SUPER_CURVE_H 
#define RS_SUPER_CURVE_H
#include "state machine/RobotState.h"
#include "state machine/StatesEnum.h"
#include <Arduino.h>
#define PEAK_MEMORY 7

class RSSuperCurve : public RobotState{
  public:
    RSSuperCurve(){}
  private:
    //===========//
    // variables //
    //===========//
    float base_speed = 40;
    float turn_modifier = 40; 
    bool curve_detected = false; // for state transision to curve logic
    //===========//
    // functions //
    //===========//
    bool full_peak_cycle_done = false;
    int peak_index = 0;
    unsigned long peak_list[PEAK_MEMORY];
    void update_amount_of_big_peaks(); // update the amount of big peaks in recent time
    int get_amount_of_big_peaks(); // get the amount of big peaks in recent time


    //====================//
    // override functions //
    //====================//
    void enter() override;
    void update() override;
    StatesEnum go_next_state() override;

    const static int curve_big_peak_treshold; // treshold for determining if the robot is in a curve or not
};
#endif
