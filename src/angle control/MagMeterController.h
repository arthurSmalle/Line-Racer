#ifndef MAGMETERCONTROLLER_H
#define MAGMETERCONTROLLER_H
#include <Arduino.h>

class MagMeterController{
  public:
    // DEBUGING FUNCTIONS
    void get_measured_data(float &x,float &y,float &z){
      x = this->x;
      y = this->y;
      z = this->z;
    }
    void get_zp_data(float &x,float &y,float &z){
      x = this->x_zp;
      y = this->y_zp;
      z = this->z_zp;
    }
    // END DEBUGGING FUNCTIONS
    void virtual update();
    int virtual init();
    int virtual get_mag_data(float &x,float &y,float &z);
    bool virtual is_mag_ready();
    
    float get_angle_to_zero();
    bool get_angle_ref_set(){return  this->angle_ref_set;}
    bool get_zp_set(){return this->zp_set;}
    
    void set_angle_to_magdata_ref(const float rad, const float x,const float y,const float z){
      this->angle_ref = rad;
      this->x_angle_ref =x;
      this->y_angle_ref =y;
      this->z_angle_ref =z;
      this->angle_to_tan_scale_set = false;
      this->angle_ref_set = true;
    }
    
    void set_zero_point(const float x, const float y, const float z){
      this->x_zp = x;
      this->y_zp = y;
      this->z_zp = z;
      this->zp_set = true;
      this->angle_to_tan_scale_set = false;
    } 

  protected:
    MagMeterController(){}
    float x,y,z; // working data
  private:
    void calculate_angle_to_tan_scale();

    bool angle_ref_set = false; // keep track if angle ref is set or not
    bool zp_set = false; // keep track if the zero point is already set or not
    bool angle_to_tan_scale_set = false; // (angle / tan(x/y))
    float x_zp, y_zp, z_zp; // zero point data
    // refrence data for angle to magdata
    float angle_ref;
    float x_angle_ref, y_angle_ref, z_angle_ref;
    float angle_to_tan_scale = 0; // (angle / tan(x/y))
};
#endif
