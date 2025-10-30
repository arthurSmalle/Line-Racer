#ifndef CONTROLLER_H
#define CONTROLLER_H
class Controller{
  public:

    void virtual calculate_output();
    float get_set_point(){return this->set_point;}
    float get_output_signal(){return * this->output_signal;};
    
    void  virtual set_error_signal(float * const error_signal){ this->error_signal = error_signal;};
    void virtual set_set_point(const float set_point){this->set_point = set_point;}

    Controller(float * const error_signal, float * const output_signal){
      this->error_signal = error_signal;
      this->output_signal = output_signal;
    }
    
    Controller(float * const error_signal, float * const output_signal, const float set_point): Controller(error_signal, output_signal){
      this-> set_point = set_point;
    }

  protected:
    float * error_signal;
    float * output_signal;
    float set_point;
};
#endif
