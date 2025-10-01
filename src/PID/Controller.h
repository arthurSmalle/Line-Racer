class Controller{
  public:
    float error_signal;
    float output_signal;

    float get_output_signal(){return this->output_signal;};
    void set_error_signal(const float &error_signal){ this->error_signal = error_signal;};

    Controller(float &error_signal, float &output_signal){
      this->error_signal = error_signal;
      this->output_signal = output_signal;
    };
};
