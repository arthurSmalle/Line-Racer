#ifndef TACHOMETER_H
#define TACHOMETER_H

enum tacho_err_t {tacho_ok, tacho_err_not_en, tacho_err_no_prev};

class Tachometer{
  public:
    void enable();
    void disable();
    tacho_err_t calculate_rpm();
    float get_rpm(){return this->rpm;}

    bool get_en_status(){return is_enabled;}
  private:
    float rpm = 0;
    bool is_enabled = false;
    bool just_enabled = false;
    unsigned long prev_time; // previous time the tachometer measured a rotation
    void set_new_prev_time();
};
#endif
