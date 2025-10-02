#ifndef CONTROLLER_H
#define CONTROLLER_H
class Controller{
  public:
    float error_signal;
    float output_signal;

    float get_output_signal(){return this->output_signal;};
    void virtual set_error_signal(const float &error_signal){ this->error_signal = error_signal;};

    Controller(const float &error_signal){
      this->error_signal = error_signal;
    };
};
#endif
