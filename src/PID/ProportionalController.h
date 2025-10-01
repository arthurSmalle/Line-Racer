#include "Controller.h"
class ProportionalController : Controller{

  public:
    float Kp;

    ProportionalController(float Kp, float &error_signal, float &output_signal): Controller(error_signal, output_signal) {
      this->Kp = Kp;
    };

    float get_output_signal(){return this->output_signal;};
    void set_error_signal(const float &error_signal){ this->error_signal = error_signal;};

// later obfuscate this function
    void calculate_output(){
      this->output_signal = Kp * error_signal;
    };
};
