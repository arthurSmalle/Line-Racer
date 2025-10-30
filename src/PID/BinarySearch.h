#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H
#include "Controller.h"

class BinarySearch : public Controller{
  public:
    BinarySearch(const float &error_signal,const float set_point,const float min, const float max, const float resolution): Controller(error_signal){
      this->set_point = set_point;
      this->resolution = resolution;
      this->min = min;
      this->max = max;
    }
  bool calculate_output(); // calculate_output, returns true when done calculating
  void set_error(float error_signal){this->error_signal = error_signal;}

  private:
    float set_point;
    float resolution;
    float min;
    float max;
};
#endif
