// Abstract monitoring class
class Monitor{
  public:
   float get(){ return monitored_data;} // get data from sensor that is monitored
   virtual void refresh_data(); // refresh the held sensor data

  protected:
   float monitored_data; // stored sensor data
};

// classes that do real life measurements
class SpeedMonitor final : public Monitor{
  public:
    void refresh_data() override;
};

class AngleMonitor final : public Monitor{
  public:
    void refresh_data() override;
  private:
    float ir_sens_estimate();
};
