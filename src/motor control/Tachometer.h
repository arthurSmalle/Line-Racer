// FOR THE MOMENT THERE CAN ONLY BE 2 TACHOMETER OBJECTS
#ifndef TACHOMETER_H
#define TACHOMETER_H
#include <Arduino.h>
#include <cstdint>

enum tacho_err_t {tacho_ok, tacho_err_not_en, tacho_err_no_prev};

class Tachometer{
  public:
    void enable();
    void disable();
    tacho_err_t calculate_rpm();
    float get_rpm(){return this->rpm;}

    bool get_en_status(){return is_enabled;}

    Tachometer(const uint8_t pin,const uint8_t id){
      this->pin = pin;
      this->id = id;
    }
  private:
    uint8_t pin;
    float rpm = 0;
    bool is_enabled = false;
    bool just_enabled = false;
    // used as glue function (NOT CLEAN CODE)
    uint8_t id;
    static volatile unsigned long prev_time[2]; // previous time the tachometer measured a rotation
    static void set_new_prev_time0(){prev_time[0] = millis();};
    static void set_new_prev_time1(){prev_time[1] = millis();};
};
#endif
