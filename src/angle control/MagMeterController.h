#ifndef MAGMETERCONTROLLER_H
#define MAGMETERCONTROLLER_H

class MagMeterController{
  public:
    float get_angle_to_zero();
    int virtual get_mag_data(float &x,float &y,float &z);
    bool virtual is_mag_ready();
    void virtual set_angle_to_magdata_ref(const float rad, const float x,const float y,const float z){
      this->angle_ref = rad;
      this->x_angle_ref =x;
      this->y_angle_ref =y;
      this->z_angle_ref =z;
    }
    
    bool get_angle_ref_set(){return  this->angle_ref_set;}
    bool get_zp_set(){return this->zp_set;}
  protected:
    MagMeterController(){}
    // calibrate the zero point of the magnetometer
    void virtual set_zero_point(const float x, const float y, const float z){
      this->x_zp = x;
      this->y_zp = y;
      this->z_zp = z;
      this->zp_set = true;
    } 
  private:
    bool angle_ref_set = false; // keep track if angle ref is set or not
    bool zp_set = false; // keep track if the zero point is already set or not
    float x,y,z; // working data
    float x_zp, y_zp, z_zp; // zero point data
    // refrence data for angle to magdata
    float angle_ref;
    float x_angle_ref, y_angle_ref, z_angle_ref;
};
#endif
