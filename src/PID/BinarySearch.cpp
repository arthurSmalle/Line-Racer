#include "BinarySearch.h"

bool BinarySearch::calculate_output(){
  // check if the error signal is in the tolerance area
  if ((this->error_signal < (this->set_point + this->resolution)) || (this->error_signal > (this->set_point - this->resolution))){
    return true;
  }
  if (this->error_signal > this->set_point){
    this->error_signal = error_signal;
    this->error_signal = this->max - this->min;
  } else if (this->error_signal < this->set_point){
    this->max = error_signal;
    this->error_signal = this->max - this->min;
  }
  return false;
}
